cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")
project(Raylite_project)

#Bring the headers into the project
include_directories(include)

#Add sources:
file(GLOB SOURCES "src/*.cpp")

add_executable(bin/raylite ${SOURCES})
