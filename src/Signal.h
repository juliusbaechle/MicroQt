#pragma once

#include "Vector.h"
#include "Function.h"
#include <Arduino.h>

namespace MicroQt {
  template<typename ... Args>
  class Signal {
  public:
    void operator()(Args ... a_params);

    uint32_t connect(function<void(Args ...)> a_function);
    void disconnect(uint32_t a_connectionId);

  private:
    uint32_t m_lastConnectionId = 0;
    Vector<uint32_t> m_connectionIds;
    Vector<function<void(Args ...)>> m_callbacks;
  };

  #include "Signal.hpp"
}
