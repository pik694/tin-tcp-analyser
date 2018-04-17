cmake_minimum_required(VERSION 3.10)
project(unix-tcp-analyser)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.60.0 REQUIRED COMPONENTS program_options system unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(src)

add_subdirectory(tests)