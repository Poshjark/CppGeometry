cmake_minimum_required(VERSION 2.4)

project(geometry LANGUAGES CXX)

include_directories(${PROJECT_SOURCE_DIR})
add_library(geometry_lib geometry.cpp geometry.h)

add_executable(geo main.cpp)
set_property(TARGET geo PROPERTY CXX_STANDARD 17)
target_link_libraries(geo geometry_lib)


