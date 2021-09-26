#pragma once

#include <Arduino.h>
#include "EventLoop.h"
#include "Timer.h"

template<typename T>
struct initializer_list {
  template<size_t N>
  initializer_list(const T (&a_arr) [N]) {
    size = N;
    m_arr = a_arr;
  }

private:
  const T* m_arr;
  uint16_t size;
};

const char arr[] = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', 0 };

TEST(Timer, can_start_stop_resume) {
  Timer timer1(25);
  Timer timer2(65);

  timer1.sglTimeout.connect([&]() {
    timer2.isActive()
      ? timer2.stop()
      : timer2.resume();
  });

  timer2.sglTimeout.connect([]() { 
    EventLoop::topLevelLoop().exit(0); 
  });

  uint32_t startMs = millis();
  timer1.start();
  timer2.start();

  EventLoop::topLevelLoop().exec();
  uint32_t elapsed = millis() - startMs;
  ASSERT_NEAR(elapsed, 125, 20);
}

TEST(EventLoop, can_use_local_event_loops) {
  Timer timer;
  timer.start(10);

  EventLoop localLoop1;
  timer.sglTimeout.connect([&]() { 
    localLoop1.isRunning()
      ? localLoop1.exit(1)
      : localLoop1.exec();

    EventLoop::topLevelLoop().exit(1);
  });

  ASSERT_EQ(EventLoop::topLevelLoop().exec(), 1);
}