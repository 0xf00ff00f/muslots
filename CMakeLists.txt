option(MUSLOTS_TEST "Generate tests" OFF)

cmake_minimum_required(VERSION 3.12)

project(muslots)

set(CMAKE_CXX_STANDARD 20)

add_library(muslots INTERFACE)
target_include_directories(muslots INTERFACE ${PROJECT_SOURCE_DIR}/include)

if (MUSLOTS_TEST)
    add_subdirectory(test)
endif ()
