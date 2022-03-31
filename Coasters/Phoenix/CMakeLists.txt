cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
set(CMAKE_CXX_FLAGS "-DRPI")
project(tests)


include_directories(
    Actuators
    States
    ${CMAKE_SOURCE_DIR}/rc-switch
    ${CMAKE_SOURCE_DIR}/BlockManager/include
)


add_executable(phoenix phoenix.cpp)

find_library(WIRINGPI_LIBRARIES NAMES wiringPi REQUIRED)
find_library(SERVO_LIBRARIES NAMES wiringPiPca9685 REQUIRED)

target_link_libraries(phoenix
    ${WIRINGPI_LIBRARIES}
    ${SERVO_LIBRARIES}
    rc-switch
)