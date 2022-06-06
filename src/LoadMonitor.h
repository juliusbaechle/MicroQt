#pragma once

class LoadMonitor {
public:
  void update(int a_busyMs, int a_idleMs);

private:
  void logRamUsage();

private:
  int m_sumBusyMs = 0;
  int m_sumIdleMs = 0;
  int m_ramLogCounter = 0;
};