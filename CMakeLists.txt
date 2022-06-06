cmake_minimum_required(VERSION 3.16)
set(PROJECT "MicroQt")
project("${PROJECT}" VERSION 0.0.0 LANGUAGES CXX)

set(LIBRARY_HEADERS    
	"src/MicroQt.h" 
	"src/EventLoop.h"
	"src/LoadMonitor.h"
	"src/Signal.h"
	"src/Signal.hpp"
	"src/Synchronizer.h"
	"src/Timer.h"
	"src/Vector.h"
	"src/Vector.hpp"
) 

set(LIBRARY_SOURCES     
	"src/EventLoop.cpp"	
	"src/LoadMonitor.cpp"
	"src/Synchronizer.cpp"	
	"src/Timer.cpp"
)

add_library(${PROJECT} INTERFACE ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(${PROJECT} INTERFACE "MicroQt")


option(ENABLE_TESTS "Builds MicroQt Tests" OFF)
if(ENABLE_TESTS)						
	set(TEST_HEADERS     
		"tests/Arduino.h"
		"tests/MicroQt_Tests.h"
	) 

	set(TEST_SOURCES     
		"tests/Arduino.cpp"
		"tests/main.cpp"
	)
	
	source_group("MicroQt" FILES ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
	source_group("Tests" FILES ${TEST_HEADERS} ${TEST_SOURCES})

	set(APP_TESTS ${PROJECT}_Tests)
	add_executable(${APP_TESTS} ${TEST_HEADERS} ${TEST_SOURCES} ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
	target_include_directories(${APP_TESTS} PUBLIC "tests" "src")
	target_link_libraries(${APP_TESTS} PUBLIC ${PROJECT})
	target_compile_features(${APP_TESTS} PUBLIC cxx_std_11)
endif()