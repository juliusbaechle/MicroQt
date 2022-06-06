#include <MicroQt.h>
using namespace MicroQt;

Timer timer1 (1000);
Timer timer2 (5000);

void setup() {
  Serial.begin(9600);
  timer1.sglTimeout.connect([](){ Serial.println("Some periodic event!"); });
  timer1.start();
}

void waitForTimer() {
  // This object is used to wait synchronously for an event
  Synchronizer synchronizer;

  // The timer will stop the execution of the synchronizer after 2 seconds
  // It is important that synchronizer.exit(1) is called only once, because it won't exist after leaving this function
  timer2.setSingleShot(true);
  timer2.sglTimeout.connect([&](){ synchronizer.exit(1); });
  timer2.start();

  // Synchronizer.exec() appears blocking within this function, but it is not.
  // In fact, control is transferred to the event loop so that tasks/timers and events are still processed
  Serial.println("waiting for timeout ...");
  int exitCode = synchronizer.exec();
  Serial.print("finished waiting with exit code: ");
  Serial.println(exitCode);
}

void loop() {
  // This event will be processed as soon as the event loop is executed
  eventLoop.enqueueEvent([](){ waitForTimer(); });
  // Transfer control to the event loop to process timers and events
  eventLoop.exec();
}
