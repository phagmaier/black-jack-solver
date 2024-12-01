cmake_minimum_required(VERSION 3.31.1)
project(Project)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
    src/main.cpp
    src/helperfunctions.cpp
)

# Create the executable
add_executable(runme ${SOURCES})

# Always apply maximum optimization (applies to all build types)
target_compile_options(runme PRIVATE -O3 -march=native -flto)

# Always enable Link Time Optimization (LTO)
target_link_options(runme PRIVATE -flto)

