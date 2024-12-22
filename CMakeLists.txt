# Minimum required CMake version
cmake_minimum_required(VERSION 3.15)

# Project name
project(ScanSense)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(src)

# Add source files dynamically
file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/analyzers/*.cpp
    src/analysisManager/*.cpp
    src/analyzerFactory/*.cpp
    src/shared/*.cpp
)

# Add the executable
add_executable(ScanSense ${SOURCES})

# Enable unit tests
# enable_testing()
# add_subdirectory(tests)

# Display build information
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
