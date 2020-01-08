cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(bulba
        VERSION 0.1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

add_executable(bulba main.cpp)

find_package(Threads REQUIRED)

target_link_libraries(bulba Threads::Threads)
