set(LIBRARY_INCLUDES    "include")

set(LIBRARY_HEADERS     "include/Arduino.h"
						"include/Callbacks.h"
						"include/EventLoop.h"
						"include/LoadMonitor.h"
						"include/Signal.h"
						"include/Timer.h"
						"include/Vector.h") 

set(LIBRARY_SOURCES     "src/Arduino.cpp"
						"src/EventLoop.cpp"
						"src/LoadMonitor.cpp"
						"src/Timer.cpp")

add_library(${LIBRARY_MICROQT} OBJECT ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(${LIBRARY_MICROQT} PUBLIC ${LIBRARY_INCLUDES})
target_compile_features(${LIBRARY_MICROQT} PUBLIC cxx_std_17)