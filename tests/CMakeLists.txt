cmake_minimum_required(VERSION 3.16)
set(PROJECT "MicroQt_Tests")
project("${PROJECT}" VERSION 0.0.0 LANGUAGES CXX)

set(LIBRARY_HEADERS    
	"../src/MicroQt.h" 
	"../src/EventLoop.h"
	"../src/LoadMonitor.h"
	"../src/Signal.h"
	"../src/Signal.hpp"
	"../src/Synchronizer.h"
	"../src/Timer.h"
	"../src/Vector.h"
	"../src/Vector.hpp"
) 

set(LIBRARY_SOURCES     
	"../src/EventLoop.cpp"	
	"../src/LoadMonitor.cpp"
	"../src/Synchronizer.cpp"	
	"../src/Timer.cpp"
)

source_group("MicroQt" FILES ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})


set(TEST_HEADERS     
	"Arduino.h"
	"MicroQt_Tests.h"
) 

set(TEST_SOURCES     
	"Arduino.cpp"
	"main.cpp"
)	

source_group("Tests" FILES ${TEST_HEADERS} ${TEST_SOURCES})
	

add_executable(${PROJECT} ${TEST_HEADERS} ${TEST_SOURCES} ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(${PROJECT} PUBLIC "." "../src")
target_compile_features(${PROJECT} PUBLIC cxx_std_11)