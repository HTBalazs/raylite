cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")
project(Raylite_project)

#Bring the headers into the project
include_directories(include)

#Add sources and includes:
file(GLOB SOURCES "src/*.cpp")
file(GLOB INCLUDES "include/*.h")

# Define library and include directories
set(STATIC_LIB_DIR /usr/local/lib/raylite)
set(INCLUDE_DIR /usr/local/include/raylite)

# set archive output to <project_directory>/lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib/)

# generate libraylite.a file
add_library(raylite STATIC ${SOURCES})

# install lib and include directories
install(TARGETS raylite DESTINATION ${STATIC_LIB_DIR})
install(FILES ${INCLUDES} DESTINATION ${INCLUDE_DIR})
