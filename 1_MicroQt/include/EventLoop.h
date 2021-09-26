#pragma once

#include "Signal.h"
#include "LoadMonitor.h"

class EventLoop {
public:
  EventLoop();
  ~EventLoop() = default;

  int exec();
  void exit(int a_exitCode);
  bool isRunning() { return !m_exit; }

  // Registrierung für zyklische Aufrufe
  Signal<> sglUpdate;

  void enqueue(function<void()> a_event);
  void enqueuePrioritized(function<void()> a_event);

public:
  static EventLoop& topLevelLoop();
  static uint8_t currentLoopLevel() { return m_loopStack.size(); }

private:
  void processEvents();

private:
  static LoadMonitor m_loadMonitor;
  static Vector<EventLoop*> m_loopStack;

  Vector<function<void()>> m_events;
  bool m_exit = true;
  int m_exitCode = 0;
};