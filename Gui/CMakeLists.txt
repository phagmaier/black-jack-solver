cmake_minimum_required(VERSION 3.15)

# Project Name and Version
project(Blackjack VERSION 1.0 LANGUAGES CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enforce Maximum Optimizations
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -flto -DNDEBUG")

# Find raylib (required)
find_package(raylib REQUIRED)

# Add Executable
add_executable(runme 
src/main.cpp
src/Parser.cpp
src/Gui)

# Link raylib to the Executable
target_link_libraries(runme PRIVATE raylib)

# Include Directories (if required)
target_include_directories(runme PRIVATE ${RAYLIB_INCLUDE_DIRS})

