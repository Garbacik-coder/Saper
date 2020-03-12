cmake_minimum_required(VERSION 3.15)
project(Saper)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -Wextra)
add_executable(Saper main.cpp cmake-build-debug/class.h cmake-build-debug/etap2.h)