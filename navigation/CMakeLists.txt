cmake_minimum_required(VERSION 3.10)
project(navigation)

set(CMAKE_CXX_STANDARD 14)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/common)

# Add executable
add_executable(navigation navigation.cpp)
