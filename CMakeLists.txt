cmake_minimum_required(VERSION 3.10.2)

set(This RandomText)

project(${This})

set(Sources
    Main.cpp
    RandomText.cpp
)

add_executable(${This} ${Sources})