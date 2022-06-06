#include "Arduino.h"
#include <chrono>
#include <iostream>
#include <thread>
using namespace std::chrono;

uint32_t millis() {
  milliseconds ms = duration_cast<milliseconds>(
    system_clock::now().time_since_epoch()
  );
  return ms.count();
}

void delay(uint32_t ms) {
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

class StdOut : public ISerial {
public:
  StdOut() {}

  void print(const char* a_text) override {
    std::cout << a_text;
  }

  void print(int a_number) override {
    std::cout << a_number;
  }

  void println(const char* a_text) override {
    std::cout << a_text << std::endl;
  }

  void println(int a_number) override {
    std::cout << a_number << std::endl;
  }

  void println() override {
    std::cout << std::endl;
  }
};

StdOut stdOut;
ISerial& Serial = stdOut;