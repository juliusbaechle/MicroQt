#pragma once

#include "Signal.h"
#include "LoadMonitor.h"

namespace MicroQt {
  class EventLoop {
    friend class Synchronizer;

  public:
    int exec();
    void exit(int a_exitCode);
    bool isRunning() { return !m_exit; }

    void enqueueEvent(function<void()> a_event) { m_events.push_back(a_event); }

    uint32_t registerTask(function<void()> a_function) { return m_taskUpdate.connect(a_function); }
    void unregisterTask(uint32_t a_connection) { return m_taskUpdate.disconnect(a_connection); }
    
  private:
    void update();
    void processEvents();

  private:
    LoadMonitor m_loadMonitor;
    Signal<> m_taskUpdate;
    Vector<function<void()>> m_events;
    bool m_exit = true;
    int m_exitCode = 0;
  };
  extern EventLoop eventLoop;
}