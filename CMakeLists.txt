cmake_minimum_required (VERSION 2.6)

project(SolidGenerator CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SRCS main.cpp generator.cpp)
set(HEADERS generator.h helpers.h solid.h)
add_executable(SolidGenerator ${SRCS} ${HEADERS})
