cmake_minimum_required(VERSION 3.10)
project(navigation)

set(CMAKE_CXX_STANDARD 14)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/common)

# Add Adafruit LSM9DS1 library include directory
include_directories(/usr/local/include/Adafruit_LSM9DS1)

# Add executable
add_executable(navigation navigation.cpp wheel.cpp)

# Link libraries
target_link_libraries(navigation pthread wiringPi Adafruit_LSM9DS1)
