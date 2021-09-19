#include "Timer.h"
#include "EventLoop.h"
#include <Arduino.h>

Timer::Timer(int a_intervalMs) {
  setInterval(a_intervalMs);
  EventLoop::mainThreadLoop().sglUpdate.connect(this, &Timer::update);
}

Timer::~Timer() {
  EventLoop::mainThreadLoop().sglUpdate.disconnect(this, &Timer::update);
}

void Timer::start(int a_intervalMs) {
  setInterval(a_intervalMs);
  m_timeElapsed = 0;
  m_startMs = millis();
  m_active = true;
}

void Timer::resume() {
  m_startMs = millis();
  m_active = true;
}

void Timer::stop() {
  m_timeElapsed += millis() - m_startMs;
  m_active = false;
}

void Timer::setInterval(int a_intervalMs) {
  if (a_intervalMs >= 0)
    m_intervalMs = a_intervalMs;
}

void Timer::update() {
  if (!m_active) return;
  
  if (m_timeElapsed + (millis() - m_startMs) >= m_intervalMs) {
    if (!m_singleShot)
      start(m_intervalMs);
    sglTimeout();
  }
}
