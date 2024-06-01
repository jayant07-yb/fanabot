cmake_minimum_required(VERSION 3.10)
project(navigation)

set(CMAKE_CXX_STANDARD 14)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/common)

# Find required libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(WIRINGPI REQUIRED wiringPi)
include_directories(${WIRINGPI_INCLUDE_DIRS})

# Include directories

# Add executable
add_executable(navigation navigation.cpp)

# Link libraries
target_include_directories(navigation PRIVATE ${CMAKE_SOURCE_DIR}common)
target_link_libraries(navigation ${WIRINGPI_LIBRARIES} common pthread)
