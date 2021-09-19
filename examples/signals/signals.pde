// Created by Julius B�chle

#include <MicroQt.h>

void print() {
  Serial.println("print");
}

void printNumber(int number) {
  Serial.println(number);
}

// Printer will be used, to show how to connect of member functions
class Printer {
public:
  void print() {
    Serial.println("Printer");
  }

  void printText(const char* text) {
    Serial.println(text);
  }
};

void setup() {
  Serial.begin(9600);
  Printer printer;

  // Non member functions are connected by the function pointer only
  Signal<int> sglPrintNumber;
  sglPrintNumber.connect(printNumber);
  sglPrintNumber(2);

  // member functions are object-bound, so you have to pass the object pointer
  Signal<const char*> sglPrintText;
  sglPrintText.connect(&printer, &Printer::printText);
  sglPrintText("Signals");
  
  // you can connect more than one slot, and even mix member and non member functions
  Signal<> sglPrint;
  sglPrint.connect(print);
  sglPrint.connect(&printer, &Printer::print);
  sglPrint();
}

void loop() {
  delay(5);
}