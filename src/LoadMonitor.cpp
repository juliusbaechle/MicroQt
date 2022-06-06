#include "LoadMonitor.h"
#include <Arduino.h>

void LoadMonitor::update(int a_busyMs, int a_idleMs) {
  m_sumBusyMs += a_busyMs;
  m_sumIdleMs += a_idleMs;

  if (m_sumBusyMs + m_sumIdleMs > 1000) {
    Serial.print("CPU Load: ");
    Serial.print((100 * m_sumBusyMs) / (m_sumBusyMs + m_sumIdleMs));
    Serial.println("%");

    m_sumBusyMs = 0;
    m_sumIdleMs = 0;
    m_ramLogCounter++;
  }

  if (m_ramLogCounter > 5) {
    m_ramLogCounter = 0;
    logRamUsage();
  }
}

void LoadMonitor::logRamUsage() {
#ifdef ARDUINO_MEGA
  // Scanning RAM takes 82 ms (Mega, 82% load)

  int size = 8192;
  byte* buf;
  while ((buf = (byte*)malloc(--size)) == NULL);
  free(buf);
  return size;

  uint8_t ramUsagePercent = 100 * (8192.0 - (float)size()) / 8192;
  Serial.print("RAM Usage: ");
  Serial.print(ramUsagePercent);
  Serial.println("%");
#else
  Serial.println("Cannot determine RAM usage");
#endif
}