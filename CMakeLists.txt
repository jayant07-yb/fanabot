cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)

project(Fanna)

# Set the path to the VL53L0X library
set(VL53L0X_DIR "/home/jayan/code/dependencies/vl53l0x-linux")
# Specify the path to the Crow library within the project
set(CROW_INCLUDE_DIR "/home/jayan/code/dependencies/Crow/include")

set(Adafruit_LSM9DS1_DIR "/home/jayan/code/dependencies/Adafruit_LSM9DS1")

# Define the source files for the project
# set(SOURCES
#     main.cpp
#     lidar_reading.cpp
#     navigation.cpp
#     server.cpp
#     ${VL53L0X_DIR}/VL53L0X.cpp
#     ${VL53L0X_DIR}/I2Cdev.cpp
# )

# # Add the executable
# add_executable(fanna ${SOURCES})

# Include directories
# target_include_directories(fanna PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     ${VL53L0X_DIR}
#     ${CROW_INCLUDE_DIR}
#     pthread
#     /usr/local/include
# )

# Link libraries
# target_link_libraries(fanna
#     pthread
#     bcm2835
# )

# Add subdirectories
add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(lidar)
add_subdirectory(navigation)