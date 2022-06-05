#include "Timer.h"
#include "EventLoop.h"
using namespace MicroQt;

Timer::Timer(int a_intervalMs) {
  setInterval(a_intervalMs);
  m_connectionId = eventLoop.registerTask([&]() { update(); });
}

Timer::~Timer() {
  eventLoop.unregisterTask(m_connectionId);
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
    m_singleShot
      ? m_active = false
      : start(m_intervalMs);
    sglTimeout();
  }
}
