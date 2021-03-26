cmake_minimum_required(VERSION 3.10.2)

set(This RandomText)

project(${This})

set(Sources
    RandomText.cpp
)

add_library(${This} ${Sources})
target_include_directories(${This} PUBLIC ./)

add_subdirectory(Demo)