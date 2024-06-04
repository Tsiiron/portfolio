cmake_minimum_required(VERSION 3.22)
project(matrix)

add_executable(${PROJECT_NAME} main.cpp Matrix.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})