#pragma once

#include <assert.h>
#include <ArduinoMock.h>
#include "EventLoop.h"
#include "Timer.h"
using namespace MicroQt;


void testSignals() {
  Signal<int> signal;
  int i = 0;

  uint32_t id = signal.connect([&](auto a_i) { i = a_i; });
  signal(3);
  assert(i == 3);

  signal.disconnect(id);
  signal(2);
  assert(i == 3);
}

void testTimers() {
  Timer timer1(25);
  Timer timer2(65);

  timer1.sglTimeout.connect([&]() {
    timer2.isActive()
      ? timer2.stop()
      : timer2.resume();
  });

  timer2.sglTimeout.connect([]() { 
    EventLoop::mainLoop().exit(0); 
  });

  uint32_t startMs = millis();
  timer1.start();
  timer2.start();

  EventLoop::mainLoop().exec();
  uint32_t elapsed = millis() - startMs;
  assert(130 < elapsed && elapsed < 170);
}

void testEventLoops() {
  Timer timer;
  timer.start(10);

  EventLoop localLoop1;
  timer.sglTimeout.connect([&]() { 
    localLoop1.isRunning()
      ? localLoop1.exit(1)
      : localLoop1.exec();

    EventLoop::mainLoop().exit(1);
  });

  assert(EventLoop::mainLoop().exec() == 1);
}