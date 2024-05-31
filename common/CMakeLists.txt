cmake_minimum_required(VERSION 3.10)
project(common)

set(CMAKE_CXX_STANDARD 14)

# Create a static library from the common functions
add_library(common STATIC shmem.cpp)

# Ensure that the include directory is available to other targets
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
