#include <MicroQt.h>

void print(const char* text) {
  Serial.println(number);
}

class Printer {
public:
  void print(const char* text) {
    Serial.println(text);
  }
};

void setup() {
  Serial.begin(9600);  
  Printer printer;

  Signal<const char*> signal;
  signal.connect(&print);
  signal.connect([&](const char* text){ printer.print(text); });
  signal.print("Hello MicroQt!");
}

void loop() {
  delay(5);
}
