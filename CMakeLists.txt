cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(potato-bulba
    VERSION 0.1.0
    LANGUAGES CXX
)

add_library(potato-bulba-obj OBJECT
    include/bulba/greeting.hpp
    src/greeting.cpp
)
target_include_directories(potato-bulba-obj
    PRIVATE
        include
)

add_library(potato-bulba
    $<TARGET_OBJECTS:potato-bulba-obj>
)
add_library(potato::bulba ALIAS potato-bulba)
target_include_directories(potato-bulba
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

#[[find_package(Threads REQUIRED)
target_link_libraries(potato-bulba
    PRIVATE
        Threads::Threads
)]]

foreach(target IN ITEMS potato-bulba-obj potato-bulba)
    set_target_properties(${target}
        PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
    )
endforeach()
