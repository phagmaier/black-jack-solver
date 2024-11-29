cmake_minimum_required(VERSION 3.31.1)
project(Project)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCES
src/main.cpp
)
add_executable(runme ${SOURCES})
