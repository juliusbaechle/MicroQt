#pragma once

#include "Signal.h"
#include "LoadMonitor.h"

class EventLoop {
public:
  EventLoop() {}

  // Creates a synchronizer while running the parent event loop
  // Use from same thread only
  EventLoop(EventLoop& a_parent);

  ~EventLoop() = default;

  int exec();
  void exit(int a_exitCode);

  // Registrierung für zyklische Aufrufe
  Signal<> sglUpdate;

  void enqueue(function<void()> a_event);
  void enqueuePrioritized(function<void()> a_event);

  void processEvents();

public:
  static EventLoop& mainThreadLoop();

private:
  static LoadMonitor m_loadMonitor;
  Vector<function<void()>> m_events;
  bool m_exit = false;
  int m_exitCode = 0;
};
