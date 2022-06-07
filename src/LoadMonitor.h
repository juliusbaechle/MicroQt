#pragma once

#include "Arduino.h"

class LoadMonitor {
public:
  void setIntervalMs(uint32_t a_intervalMs = 0) { m_intervalMs = a_intervalMs; }
  void update(uint32_t a_busyMs, uint32_t a_idleMs);

private:
  void logCpuUsage();
  void logRamUsage();
  uint32_t getFreeRam();
  constexpr uint32_t getTotalRam();

private:
  uint32_t m_intervalMs = 1000;
  uint32_t m_sumBusyMs = 0;
  uint32_t m_sumIdleMs = 0;
  uint32_t m_ramLogCounter = 0;
};