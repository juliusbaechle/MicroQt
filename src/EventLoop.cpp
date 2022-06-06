#include "EventLoop.h"
#include <Arduino.h>
#include <assert.h>
using namespace MicroQt;

EventLoop MicroQt::eventLoop;

int EventLoop::exec() {
  m_exit = false;
  while (!m_exit)
    update();
  return m_exitCode;
}

void EventLoop::update() {
  uint32_t start = millis();
  m_taskUpdate();
  processEvents();
  m_loadMonitor.update(millis() - start, 1);
  delay(5);
}

void EventLoop::processEvents() {
  while (m_events.size()) {
    auto event = m_events.at(0);
    m_events.removeAt(0);
    event();
  }
}

void EventLoop::exit(int a_exitCode) {
  enqueueEvent([a_exitCode, this]() { 
    m_exitCode = a_exitCode;
    m_exit = true;
  });
}