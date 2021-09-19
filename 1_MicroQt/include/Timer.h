#pragma once

#include "Signal.h"
#include "EventLoop.h"

class Timer {
public:
  Timer(int a_intervalMs = -1);
  ~Timer();

  void start(int a_intervalMs = -1);
  void resume();
  void stop();

  bool isActive() const { return m_active; }

  void setSingleShot(bool a_singleShot) { m_singleShot = a_singleShot; }
  bool isSingleShot() const { return m_singleShot; }

  void setInterval(int a_intervalMs);
  int interval() const { return m_intervalMs; }

public:
  Signal<> sglTimeout;

private:
  void update();

private:
  bool m_active = false;
  bool m_singleShot = false;

  uint64_t m_timeElapsed = 0;
  uint64_t m_intervalMs = 0;
  uint64_t m_startMs = 0;
};
