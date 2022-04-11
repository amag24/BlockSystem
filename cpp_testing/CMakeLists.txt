cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
set(CMAKE_CXX_FLAGS "-DRPI")
project(cpp_testing)


include_directories(
    include
    ${CMAKE_SOURCE_DIR}/rc-switch
)


add_executable(lighttest src/lighttest.cpp)
add_executable(lifttest src/lifttest.cpp)
add_executable(phototest src/photoresistor_test.cpp src/sensor.cpp)
add_executable(servotest src/servotest.cpp)


find_library(WIRINGPI_LIBRARIES NAMES wiringPi REQUIRED)
find_library(SERVO_LIBRARIES NAMES wiringPiPca9685 REQUIRED)

target_link_libraries(lighttest
${WIRINGPI_LIBRARIES}
)

target_link_libraries(phototest
${WIRINGPI_LIBRARIES}
)

target_link_libraries(lifttest
${WIRINGPI_LIBRARIES}
rc-switch
)

target_link_libraries(servotest
${WIRINGPI_LIBRARIES}
${SERVO_LIBRARIES}
)