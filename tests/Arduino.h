#pragma once

#include <stdint.h>
#include <memory>

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define F(x) x

uint32_t millis();
void delay(uint32_t ms);

class ISerial {
public:
  virtual void print(const char*) = 0;
  virtual void print(int) = 0;
  virtual void println(const char*) = 0;
  virtual void println(int) = 0;
  virtual void println() = 0;
};

extern ISerial& Serial;