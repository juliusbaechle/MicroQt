#pragma once

#include "Signal.h"
#include "LoadMonitor.h"

namespace MicroQt {
  class EventLoop {
  public:
    EventLoop();
    ~EventLoop();

    int exec();
    void exit(int a_exitCode);
    bool isRunning() { return !m_exit; }

    static void enqueueEvent(function<void()> a_event) { mainLoop().m_events.push_back(a_event); }

    static uint32_t registerTask(function<void()> a_function) { return mainLoop().m_taskUpdate.connect(a_function); }
    static void unregisterTask(uint32_t a_connection) { return mainLoop().m_taskUpdate.disconnect(a_connection); }

  public:
    static EventLoop& mainLoop();
    static uint8_t currentLoopLevel() { return m_loopStack.size(); }

  private:
    void processEvents();

  private:
    static LoadMonitor m_loadMonitor;
    static vector<EventLoop*> m_loopStack;

    Signal<> m_taskUpdate;
    vector<function<void()>> m_events;
    bool m_exit = true;
    int m_exitCode = 0;
  };
}