// Created by Julius Bächle

#include <MicroQt.h>

void print1() {
  Serial.println("1");
}

void print2() {
  Serial.println("2");
}

// Interval in ms passed through constructor
Timer timer1(1000);
Timer timer2;

void setup() {
  Serial.begin(9600);

  // Connect print1 to be executed with timer1
  timer1.sglTimeout.connect(print1);
  // Timer will be executed only once
  timer1.setSingleShot(true);
  timer1.start();

  // Set Interval in ms through function
  timer2.setInterval(2000);
  // Timer will be executed repetedly (default)
  timer2.setSingleShot(false);
  // Connect print2 to be executed with timer2
  timer2.sglTimeout.connect(print2);
  timer2.start();
}

void loop() {
  // Start Scheduling, will run until exit is called
  EventLoop::topLevelLoop().exec();
}