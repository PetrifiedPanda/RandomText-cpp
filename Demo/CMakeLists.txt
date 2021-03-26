cmake_minimum_required(VERSION 3.10.2)

set(Sources
    Main.cpp
)

add_executable(Demo ${Sources})
target_link_libraries(Demo ${This})