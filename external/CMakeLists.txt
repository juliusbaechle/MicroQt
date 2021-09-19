if(UNIT_TESTS)
	set(gtest_force_shared_crt ON CACHE BOOL "Use MDd for googletest" FORCE)
    add_subdirectory(googletest)
endif()