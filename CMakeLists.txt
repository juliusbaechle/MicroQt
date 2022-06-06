cmake_minimum_required(VERSION 3.16)
set(PROJECT "MicroQt")
project("${PROJECT}" VERSION 0.0.0 LANGUAGES CXX)

set(LIBRARY_HEADERS     
	"MicroQt/EventLoop.h"
	"MicroQt/LoadMonitor.h"
	"MicroQt/Signal.h"
	"MicroQt/Signal.hpp"
	"MicroQt/Synchronizer.h"
	"MicroQt/Timer.h"
	"MicroQt/Vector.h"
	"MicroQt/Vector.hpp"
) 

set(LIBRARY_SOURCES     
	"MicroQt/EventLoop.cpp"	
	"MicroQt/LoadMonitor.cpp"
	"MicroQt/Synchronizer.cpp"	
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
	
	source_group("MicroQt" FILES ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
	source_group("Tests" FILES ${TEST_HEADERS} ${TEST_SOURCES})
	
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