cmake_minimum_required(VERSION 3.16)
set(PROJECT "MicroQt")
project("${PROJECT}" VERSION 0.0.0 LANGUAGES CXX)

set(LIBRARY_HEADERS     
	"MicroQt/Callbacks.h"
	"MicroQt/EventLoop.h"
	"MicroQt/LoadMonitor.h"
	"MicroQt/Signal.h"
	"MicroQt/Timer.h"
	"MicroQt/vector.h"
) 

set(LIBRARY_SOURCES     
	"MicroQt/EventLoop.cpp"	
	"MicroQt/LoadMonitor.cpp"
	"MicroQt/Timer.cpp"
)

add_library(${PROJECT} INTERFACE ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(${PROJECT} INTERFACE "MicroQt")


option(ENABLE_TESTS "Builds MicroQt Tests" OFF)
if(ENABLE_TESTS)						
	set(TEST_HEADERS     
		"Tests/ArduinoMock.h"
		"Tests/MicroQt_Tests.h"
	) 

	set(TEST_SOURCES     
		"Tests/ArduinoMock.cpp"
		"Tests/main.cpp"
	)
	
	if(MSVC)
		add_definitions(/FIArduinoMock.h)
	else()
		# GCC or Clang
		add_definitions(-include "ArduinoMock.h")
	endif()

	set(APP_TESTS ${PROJECT}_Tests)
	add_executable(${APP_TESTS} ${TEST_HEADERS} ${TEST_SOURCES} ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
	target_include_directories(${APP_TESTS} PUBLIC "Tests")
	target_link_libraries(${APP_TESTS} PUBLIC ${PROJECT})
	target_compile_features(${APP_TESTS} PUBLIC cxx_std_11)
endif()