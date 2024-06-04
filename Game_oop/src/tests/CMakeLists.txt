cmake_minimum_required(VERSION 3.22)
project(tests)

set(SOURCES 
    CellTest.cpp
    PointTest.cpp
    FieldTest.cpp
    PlayerHandlerTest.cpp
    tests.cpp
)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests ${SOURCES})
target_link_libraries(tests lib ${GTEST_BOTH_LIBRARIES})