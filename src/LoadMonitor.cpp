#include "LoadMonitor.h"
#include <Arduino.h>

void LoadMonitor::update(uint32_t a_busyMs, uint32_t a_idleMs) {
  if (m_intervalMs == 0) return;

  m_sumBusyMs += a_busyMs;
  m_sumIdleMs += a_idleMs;

  if (m_sumBusyMs + m_sumIdleMs > m_intervalMs) {
    logCpuUsage();
    logRamUsage();
    Serial.println();

    m_sumBusyMs = 0;
    m_sumIdleMs = 0;
  }
}

void LoadMonitor::logCpuUsage() {
  uint32_t cpuPerc = (100 * m_sumBusyMs) / (m_sumBusyMs + m_sumIdleMs);  
  Serial.print(F("CPU Load: "));
  Serial.print(cpuPerc);
  Serial.print(F("%"));
  
  if(cpuPerc < 10) {
	  Serial.print(F("   "));
  } else if(cpuPerc < 100) {
	  Serial.print(F("  "));
  } else {
	  Serial.print(F(" "));
  }
}

void LoadMonitor::logRamUsage() {
  uint32_t totalRam = getTotalRam();
  uint32_t freeRam = getFreeRam();
  if (totalRam == 0) return;
  
  Serial.print(F("| RAM Load: "));
  Serial.print((100 * (totalRam - freeRam)) / totalRam);
  Serial.print(F("% ("));
  Serial.print(totalRam - freeRam);
  Serial.print(F(" of "));
  Serial.print(totalRam);
  Serial.print(F(" bytes)"));
}

// Kopiert von https://playground.arduino.cc/Code/AvailableMemory/
uint32_t LoadMonitor::getFreeRam() {
  #ifdef ARDUINO
    extern int __heap_start, *__brkval;
    int v;
    return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
  #else
    return 0;
  #endif
}

constexpr uint32_t LoadMonitor::getTotalRam() {
  #ifdef RAMSTART && RAMEND
    return (RAMEND - RAMSTART) + 1;
  #else
    return 0;
  #endif
}