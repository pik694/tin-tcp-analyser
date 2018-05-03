cmake_minimum_required(VERSION 3.10)
project(unix-tcp-analyser)

set(CMAKE_CXX_STANDARD 17)
if (UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS -pthread)
endif ()

find_package(Boost 1.66 REQUIRED COMPONENTS system program_options unit_test_framework)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(./src/)


add_subdirectory(src)

add_subdirectory(tests)