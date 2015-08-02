cmake_minimum_required(VERSION 3.2)

project(datetime)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES suit.cpp)

add_executable(datetime ${SOURCE_FILES})

add_subdirectory(source)
add_dependencies(${PROJECT_NAME} so.datetime)
target_link_libraries(${PROJECT_NAME} so.datetime)
