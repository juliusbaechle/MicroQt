#pragma once

#include <Arduino.h>
#include "EventLoop.h"
#include "Timer.h"

TEST(Timer, can_start_stop_resume) {
  uint32_t startMs = millis();
  Timer timer1(25);
  Timer timer2(65);

  timer1.sglTimeout.connect([&]() {
    timer2.isActive()
      ? timer2.stop()
      : timer2.resume();
  });

  timer2.sglTimeout.connect([]() { 
    EventLoop::mainThreadLoop().exit(0); 
  });

  timer1.start();
  timer2.start();

  EventLoop::mainThreadLoop().exec();
  uint32_t elapsed = millis() - startMs;
  ASSERT_NEAR(elapsed, 125, 20);
}

TEST(EventLoop, can_use_local_event_loops) {
  EventLoop localLoop(EventLoop::mainThreadLoop());
  Timer timer(10);
  timer.start();
  timer.sglTimeout.connect([&]() { localLoop.exit(1); });
  ASSERT_EQ(localLoop.exec(), 1);
}