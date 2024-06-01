cmake_minimum_required(VERSION 3.10)
project(navigation)

set(CMAKE_CXX_STANDARD 14)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/common)

# Add executable
add_executable(navigation navigation.cpp wheel.cpp)

# Link libraries
target_include_directories(navigation PRIVATE /usr/local/include ${CMAKE_SOURCE_DIR}/common)
target_link_libraries(navigation common pthread)
