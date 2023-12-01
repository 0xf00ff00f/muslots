cmake_minimum_required(VERSION 3.12)

project(muslots)

option(MUSLOTS_TEST "Build example" OFF)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(muslots)

if (MUSLOTS_EXAMPLE)
    add_subdirectory(example)
endif ()
