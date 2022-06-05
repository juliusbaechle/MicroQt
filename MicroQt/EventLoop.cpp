#include "EventLoop.h"
#include <assert.h>
using namespace MicroQt;

vector<EventLoop*> EventLoop::m_loopStack ({ new EventLoop() });
LoadMonitor EventLoop::m_loadMonitor;

EventLoop::EventLoop() {
  if (!m_loopStack.isEmpty()) {
    EventLoop& parent = *m_loopStack.last();
    m_taskUpdate.connect([&]() {
      parent.m_taskUpdate();
      parent.processEvents();
    });
  }

  m_loopStack << this;
}

EventLoop::~EventLoop() {
  if (m_loopStack.size() > 1)
    m_loopStack.removeLast();
}

int EventLoop::exec() {
  m_exit = false;

  while (!m_exit) {
    uint32_t start = millis();
    m_taskUpdate();
    processEvents();
    m_loadMonitor.update(millis() - start, 2);
    delay(1);
  }

  return m_exitCode;
}

void EventLoop::processEvents() {
  while(m_events.size()) {
    m_events.at(0)();
    m_events.remove(0);
  }
}

void EventLoop::exit(int a_exitCode) {
  enqueueEvent([a_exitCode, this]() { 
    m_exitCode = a_exitCode;
    m_exit = true;
  });
}

EventLoop& EventLoop::mainLoop() { 
  assert(!m_loopStack.isEmpty());
  return *m_loopStack.first();
}
