cmake_minimum_required(VERSION 3.16.3)
project(park_AaDS_hw)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(
        -Werror
        -Wall
        -Wextra
        -Wpedantic
)
if(TEST_WEATHER)
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()

add_executable(park_AaDS_hw main.cpp)