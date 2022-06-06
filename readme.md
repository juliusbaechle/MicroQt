[![Arduino Lint](https://github.com/juliusbaechle/MicroQt/actions/workflows/main.yml/badge.svg)](https://github.com/juliusbaechle/MicroQt/actions/workflows/main.yml)

Signals, Timers and load monitoring EventLoops enable event driven applications for Arduino.
The Qt-concept of signals & slots was inspiration for this projekt.

## Installation
To install this library, just place this entire folder as a subfolder in your
Arduino/lib/targets/libraries folder.

## Building
After this library is installed, you just have to start the Arduino application.
You may see a few warning messages as it's built.

To use this library in a sketch, go to the Sketch | Import Library menu and
select Test.  This will add a corresponding line to the top of your sketch:
#include <MicroQt.h>

To stop using this library, delete that line from your sketch.
