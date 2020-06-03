cmake_minimum_required(VERSION 3.15)
project(test)

set(CMAKE_CXX_STANDARD 11)


if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wno-unused-variable ")
else( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set(CMAKE_BUILD_TYPE "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")
endif( CMAKE_BUILD_TYPE STREQUAL "Debug" )

add_executable(test main.cpp)