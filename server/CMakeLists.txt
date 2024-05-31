cmake_minimum_required(VERSION 3.10)
project(server)

set(CMAKE_CXX_STANDARD 14)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/common)

# Add executable
add_executable(server server.cpp)
