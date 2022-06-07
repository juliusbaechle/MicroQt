#include <MicroQt.h>
using namespace MicroQt;

// Interval in ms passed through constructor
Timer singleShotTimer (1000);
Timer periodicTimer;
bool on = false;

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
  periodicTimer.sglTimeout.connect([](){ Serial.println("periodic timeout"); digitalWrite(13, on = !on); });
  periodicTimer.start();
}

void loop() {
  // Set the CPU/RAM utilization logging interval (0 deactivates it)
  eventLoop.setLogIntervalMs(2000);
  // Transfer control to the eventLoop to process tasks like timers
  eventLoop.exec();
}
