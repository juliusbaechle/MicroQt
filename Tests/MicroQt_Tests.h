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
    eventLoop.exit(0); 
  });

  uint32_t startMs = millis();
  timer1.start();
  timer2.start();

  eventLoop.exec();
  uint32_t elapsed = millis() - startMs;
  assert(130 < elapsed && elapsed < 170);
}

#include "Synchronizer.h"
void testSynchronizer() {
  Synchronizer synchronizer;
  eventLoop.enqueueEvent([&]() {
    eventLoop.enqueueEvent([&]() {
      synchronizer.exit(1);
    });

    int i = synchronizer.exec();
    eventLoop.exit(i);
  });

  assert(eventLoop.exec() == 1);
}