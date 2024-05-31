cmake_minimum_required(VERSION 3.10)
project(server)

set(CMAKE_CXX_STANDARD 14)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/common)


# Add executable
add_executable(server server.cpp )

# Link the common static library and other necessary libraries
target_link_libraries(server common bcm2835 pthread)

# Ensure that the common and crow include directories are available
target_include_directories(server PRIVATE ${CMAKE_SOURCE_DIR}/common 
                                        ${CROW_INCLUDE_DIR})
