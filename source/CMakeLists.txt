cmake_minimum_required(VERSION 2.8.4)

project(so.datetime)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(SOURCE_FILES
    decode.cpp
    encode.cpp
)

add_library(so.datetime STATIC ${SOURCE_FILES})
include_directories(../include)
