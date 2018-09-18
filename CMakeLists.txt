cmake_minimum_required (VERSION 2.6)

project(HelloWorld CXX)

set(SRCS main.cpp generator.cpp)
set(HEADERS generator.h)
add_executable(HelloWorld ${SRCS} ${HEADERS})
