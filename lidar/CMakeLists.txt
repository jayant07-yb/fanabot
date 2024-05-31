cmake_minimum_required(VERSION 3.10)
project(lidar)

set(CMAKE_CXX_STANDARD 14)

# Add executable
add_executable(lidar_executable lidar.cpp)

# Link the common static library and other necessary libraries
target_link_libraries(lidar_executable common bcm2835 pthread)

# Ensure that the common and VL53L0X include directories are available
target_include_directories(lidar_executable PRIVATE ${CMAKE_SOURCE_DIR}/common ${VL53L0X_DIR}/VL53L0X)
