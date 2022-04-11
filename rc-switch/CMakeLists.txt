cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
set(CMAKE_CXX_FLAGS "-DRPI")
project(rc-switch)


add_library(rc-switch STATIC RCSwitch.h RCSwitch.cpp)