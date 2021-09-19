#include "EventLoop.h"
#include <Arduino.h>

LoadMonitor EventLoop::m_loadMonitor;
EventLoop m_mainThreadLoop;

EventLoop::EventLoop(EventLoop& a_parent) {
  sglUpdate.connect([&]() {
    a_parent.sglUpdate();
    a_parent.processEvents();
  });
}

int EventLoop::exec() {
  while (!m_exit) {
    uint32_t start = millis();
    sglUpdate();
    processEvents();
    delay(1);
    m_loadMonitor.update(millis() - start, 3);

    delay(3);
  }
    
  m_exit = false;
  return m_exitCode;
}

void EventLoop::processEvents() {
  while(m_events.size()) {
    m_events.at(0)();
    m_events.remove(0);
  }
}

void EventLoop::exit(int a_exitCode) {
  enqueue([a_exitCode, this]() { 
    m_exitCode = a_exitCode;
    m_exit = true;
  });
}

void EventLoop::enqueue(function<void()> a_event) {
  m_events.push_back(a_event);
}

void EventLoop::enqueuePrioritized(function<void()> a_event) {
  m_events.insert(0, a_event);
}

EventLoop& EventLoop::mainThreadLoop() { 
  return m_mainThreadLoop; 
}
