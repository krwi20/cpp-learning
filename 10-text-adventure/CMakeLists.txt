cmake_minimum_required(VERSION 3.10)
project(TextAdventure VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Shared source files (all class implementations)
set(SOURCES
    src/Player.cpp
    src/Room.cpp
    src/Enemy.cpp
    src/Game.cpp
)

# Include directories
include_directories(include)

# Main game
add_executable(adventure src/main.cpp ${SOURCES})

# Tests
enable_testing()
add_executable(runTests tests/test_Player.cpp tests/catch_amalgamated.cpp ${SOURCES})
target_include_directories(runTests PRIVATE include tests)