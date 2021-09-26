#include "EventLoop.h"
#include <Arduino.h>
#include <assert.h>

Vector<EventLoop*> EventLoop::m_loopStack ({ new EventLoop() });
LoadMonitor EventLoop::m_loadMonitor;

EventLoop::EventLoop() {
  if (!m_loopStack.isEmpty()) {
    EventLoop& parent = *m_loopStack.last();
    sglUpdate.connect([&]() {
      parent.sglUpdate();
      parent.processEvents();
    });
  }

  m_loopStack << this;
}

int EventLoop::exec() {
  m_exit = false;
  while (!m_exit) {
    uint32_t start = millis();
    sglUpdate();
    processEvents();
    m_loadMonitor.update(millis() - start, 2);
    delay(1);
  }

  if(m_loopStack.size() > 1)
    m_loopStack.removeLast();
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

EventLoop& EventLoop::topLevelLoop() { 
  assert(!m_loopStack.isEmpty());
  return *m_loopStack.first();
}
