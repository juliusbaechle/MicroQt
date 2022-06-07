#include <MicroQt.h>
using namespace MicroQt;

// Interval in ms passed through constructor
Timer singleShotTimer (1000);
Timer periodicTimer;

void setup() {
  Serial.begin(9600);

  // Connect your action to the timeout signal
  singleShotTimer.sglTimeout.connect([](){ Serial.println("single shot"); });
  // A singleshot timer will be executed only once (default is periodic)
  singleShotTimer.setSingleShot(true);
  singleShotTimer.start();

  // The interval can also be set through the setIntervalMs()-function
  periodicTimer.setIntervalMs(2000);
  // The timer is executed repeatedly, which is the default behaviour
  periodicTimer.setSingleShot(false);
  periodicTimer.sglTimeout.connect([](){ Serial.println("periodic timeout"); });
  periodicTimer.start();
}

void loop() {
  // Transfer control to the eventLoop to process tasks like timers
  eventLoop.exec();
}
