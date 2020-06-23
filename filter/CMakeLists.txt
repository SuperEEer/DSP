cmake_minimum_required(VERSION 3.13)
project(filter)

set(CMAKE_CXX_STANDARD 14)

add_executable(filter main.c FFT.h Signal.h Filter_Coff.h Conv.h)
TARGET_LINK_LIBRARIES(filter  libm.so)