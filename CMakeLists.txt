cmake_minimum_required(VERSION 3.12.0)
project(bubbles)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(raylib REQUIRED)

add_subdirectory(src)
add_subdirectory(lib/inipp)

add_compile_options(-Wall -Wextra -Wpedantic)
add_link_options(-fsanitize=leak)
