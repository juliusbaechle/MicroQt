cmake_minimum_required(VERSION 3.10)

set(PROJECT "MicroQt")
project("${PROJECT}_Project" VERSION 0.0.1 LANGUAGES CXX)

# Global CMake variables are set here
set(CMAKE_CXX_STANDARD              11)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            OFF)

# Options for generating/building
option(UNIT_TESTS	"Use Unit Tests"	ON)

set(LIBRARY_MICROQT "1_MicroQt")
add_subdirectory(1_MicroQt)

if(UNIT_TESTS)		
	set(gtest_force_shared_crt ON CACHE BOOL "Use MDd for googletest" FORCE)
	add_subdirectory(external/googletest)
	
	set(APP_TEST "2_Unit_Tests")
	add_subdirectory(2_Unit_Tests)
endif()