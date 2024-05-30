cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)

project(Fanna)

# Set the path to the VL53L0X library
set(VL53L0X_DIR "/home/jayan/code/dependencies/vl53l0x-linux")
# Specify the path to the Crow library within the project
set(CROW_INCLUDE_DIR "/home/jayan/code/dependencies/Crow/include")

# Define the source files for the project
set(SOURCES
    main.cpp
    lidar_reading.cpp
    navigation.cpp
    ${VL53L0X_DIR}/VL53L0X.cpp
    ${VL53L0X_DIR}/I2Cdev.cpp
)

# Add the executable
add_executable(fanna ${SOURCES})

# Include directories
target_include_directories(fanna PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${VL53L0X_DIR}
    ${CROW_INCLUDE_DIR}
    pthread
    /usr/local/include
)

# Link libraries
target_link_libraries(fanna
    pthread
    bcm2835
)

# Examples from the library
set(VL53L0X_EXAMPLES
    single
    singleMinimal
    continuousMultipleSensors
)

foreach (example ${VL53L0X_EXAMPLES})
    add_executable(${example}
        ${VL53L0X_DIR}/VL53L0X.cpp
        ${VL53L0X_DIR}/I2Cdev.cpp
    )
    target_include_directories(${example} PUBLIC
        ${VL53L0X_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
    target_link_libraries(${example}
        pthread
        bcm2835
    )
endforeach (example)
