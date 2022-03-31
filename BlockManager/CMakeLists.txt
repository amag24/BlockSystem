cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(BlockManager)


include_directories(
    include
)


add_library(${PROJECT_NAME}
    src/manager.cpp
    src/blocksection.cpp
    src/sensor.cpp
)

find_library(WIRINGPI_LIBRARIES NAMES wiringPi REQUIRED)

target_link_libraries(${PROJECT_NAME}
    ${WIRINGPI_LIBRARIES}
)

