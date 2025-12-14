# CMakeLists.txt

# Require CMake 3.10 or higher (standard for modern C++)
cmake_minimum_required(VERSION 3.10)

# Name your project
project(TextAdventure VERSION 1.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory so headers are found
include_directories(include)

# Collect all source files
file(GLOB SOURCES "src/*.cpp")

# Create an executable named 'adventure'
add_executable(adventure ${SOURCES})

# Optional: make debug builds the default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()