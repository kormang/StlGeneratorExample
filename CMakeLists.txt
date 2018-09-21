cmake_minimum_required (VERSION 2.6)

project(SolidGenerator CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories( ${CMAKE_SOURCE_DIR}/include)

set(SRCS src/main.cpp src/generator.cpp)
set(HEADERS include/generator.h include/helpers.h include/solid.h)
add_executable(SolidGenerator ${SRCS} ${HEADERS})
