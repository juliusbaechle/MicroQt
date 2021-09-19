#pragma once

#include <stdint.h>

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))

uint32_t millis();
void delay(uint32_t ms);

class ISerial {
public:
  virtual void print(const char*) = 0;
  virtual void print(int) = 0;
  virtual void println(const char*) = 0;
};

extern ISerial& Serial;