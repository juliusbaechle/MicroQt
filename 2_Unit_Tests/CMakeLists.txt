set(APP_INCLUDES	"${PROJECT_SOURCE_DIR}/${APP_RECEPTION_MOCK}/include/"
					"${PROJECT_SOURCE_DIR}/external/googletest/googletest/include"
					"${PROJECT_SOURCE_DIR}/external/googletest/googlemock/include"
					"include")	

set(APP_HEADERS		"include/MicroQt_Tests.h")

set(APP_SOURCES     "src/main.cpp")

add_executable(${APP_TEST} ${APP_SOURCES} ${APP_HEADERS})
target_compile_options(${APP_TEST} PUBLIC "-MDd")
target_link_libraries(${APP_TEST} PUBLIC gtest gmock ${LIBRARY_MICROQT})
target_include_directories(${APP_TEST} PUBLIC ${APP_INCLUDES})
target_compile_features(${APP_TEST} PUBLIC cxx_std_17)