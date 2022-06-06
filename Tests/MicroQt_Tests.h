#pragma once

#include <assert.h>
#include <ArduinoMock.h>
#include "MicroQt.h"
using namespace MicroQt;

void testVector() {
  Vector<uint8_t> vector;
  vector.append(1);
  vector << 2 << 3;
  vector.insert(0, 0);

  Vector<uint8_t> vector2;
  vector2 << 0 << 1 << 2 << 3;
  assert(vector == vector2);

  assert(vector.size() == 4);
  assert(vector.indexOf(2) == 2);
  assert(vector[3] == 3);
  assert(vector.at(1) == 1);
  
  vector.removeAll(2);
  vector.removeAt(1);
  assert(vector[0] == 0);
  assert(vector[1] == 3);

  assert(vector.take(0) == 0);
  assert(vector[0] == 3);

  vector.clear();
  assert(vector.isEmpty());
}

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
  Timer timer1(125);
  timer1.sglTimeout.connect([&]() { eventLoop.exit(1); });
  timer1.start();

  uint32_t counter = 0;
  Timer timer2(50);
  timer2.sglTimeout.connect([&]() {
    counter++;
    timer1.isActive() ? timer1.stop() : timer1.resume();
  });
  timer2.start();

  eventLoop.exec();
  assert(counter == 4);
}

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