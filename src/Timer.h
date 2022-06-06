#pragma once

#include "Signal.h"
#include <Arduino.h>

namespace MicroQt {
  class Timer {
  public:
    Timer(uint32_t a_intervalMs = 0);
    ~Timer();

    void start();
    void start(uint32_t a_intervalMs);
    void resume();
    void stop();

    bool isActive() const { return m_active; }

    void setSingleShot(bool a_singleShot) { m_singleShot = a_singleShot; }
    bool isSingleShot() const { return m_singleShot; }

    void setInterval(uint32_t a_intervalMs) { m_intervalMs = a_intervalMs; }
    uint32_t interval() const { return m_intervalMs; }

  public:
    Signal<> sglTimeout;

  private:
    void update();

  private:
    bool m_active = false;
    bool m_singleShot = false;

    uint32_t m_connectionId = 0;
    uint32_t m_timeElapsed = 0;
    uint32_t m_intervalMs = 0;
    uint32_t m_startMs = 0;
  };
}