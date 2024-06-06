cmake_minimum_required(VERSION 3.25)
project(Zadanie_3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Zadanie_3 main.cpp)

MATH(EXPR stack_size "32 * 1024 * 1024") # 16 Mb
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")