# MicroQt Library 
[![Arduino Lint](https://github.com/juliusbaechle/MicroQt/actions/workflows/main.yml/badge.svg)](https://github.com/juliusbaechle/MicroQt/actions/workflows/main.yml)
[![Total Alerts](https://img.shields.io/lgtm/alerts/g/juliusbaechle/MicroQt.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/juliusbaechle/MicroQt/alerts/)
[![Language Grade](https://img.shields.io/lgtm/grade/cpp/g/juliusbaechle/MicroQt.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/juliusbaechle/MicroQt/context:cpp)

Library that enables event driven applications on the Arduino platform. 
This is realized by load monitoring event loops, timers and signals similar to those in the Qt framework.

## Installation
### First Method - Arduino IDE Library Manager
1. In the Arduino IDE, navigate to Sketch > Include Library > Manage Libraries
2. Then the Library Manager will open and you will find a list of libraries that are already installed or ready for installation.
3. Then search for MicroQt using the search bar.
4. Click on the text area and then select the specific version and install it.

### Second Method - Manual Installation
1. Navigate to the [Releases page](https://github.com/juliusbaechle/MicroQt/releases).
2. Download the latest release.
3. Extract the zip file
4. In the Arduino IDE, navigate to Sketch > Include Library > Add .ZIP Library

## Features
- ### Signals
  Signals make it easy to implement the observer pattern while avoiding the boilerplate code. 
  You can send signals with type-correct event information to connected callback functions and object member functions.
  This may be used for timeouts, user interfaces like buttons and asynchronous I/O.

- ### EventLoop
  MicroQt has an event loop that must be executed in the loop() function.
  Tasks registered in that event loop are called periodically. The built-in timers register 
  themselves, but you can also register your own tasks, such as polling for button state changes.
  In addition, you can enqueue events whose execution is delayed until the control returns to the event loop.
  Since they block the event loop, it is important that tasks and events can be processed quickly.
  Every second, the event loop prints the CPU and RAM usage to get an overview of the current load.

- ### Timers
  Timers are used to call functions periodically or once after a specified interval. 
  Since they run in the event loop and a task or event can block it, 
  the correct timing cannot be guaranteed, but it is appropriate in most cases.
  
- ### Synchronizers
  Synchronizers can be used to wait for a specific event, like a WiFi connection at startup.
  They appear to block, but in fact they transfer control to the event loop, 
  so that it can continue to process timers and events.

## Examples
There are several examples implemented in this library. One of the examples is below.
You can find other examples [here](https://github.com/juliusbaechle/MicroQt/tree/master/examples)

### Timers
```Cpp
#include <MicroQt.h>
using namespace MicroQt;

Timer singleShotTimer (1000);
Timer periodicTimer (2000);

void setup() {
  Serial.begin(9600);

  singleShotTimer.sglTimeout.connect([](){ Serial.println("single shot"); });
  singleShotTimer.setSingleShot(true);
  singleShotTimer.start();

  periodicTimer.sglTimeout.connect([](){ Serial.println("periodic timeout"); });
  periodicTimer.start();
}

void loop() {
  eventLoop.exec();
}
```

## Contributing

### How To Contribute 
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell others about this library
- Contribute new protocols

### Contributing Guidelines
 - Be friendly: It's my first public library and I've put in a lot of time and work, so please be patient.
 - Use reasonable titles: refrain from using overly long or capitalized titles
 - Be detailed: refrain from mentioning code problems without sharing your source code 
   and always give information regarding your board and version of the library

### ToDo List
- Refactor the Vector-Class while preserving its interface. The current implementation is very inefficient.
