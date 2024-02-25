cmake_minimum_required(VERSION 3.12.0)
project(bubbles)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)

find_package(raylib REQUIRED)

file(GLOB PROJECT_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h*"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/*/*.h*"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*"
)

# Defines related to I/O, see src/util.cpp
add_definitions(-DCFG_RELATIVE_PATH=\"bubbles.ini\")
add_definitions(-DPATH_BUFFER_SIZE=256)

# Debug defines
#add_definitions(-DDEBUG_MOUSESHOOTER)
add_definitions(-DDEBUG_SPRINKLER)
add_definitions(-DDEBUG_LISSAJOUS)

add_compile_options(-Wall -Wextra -Wpedantic)
add_link_options(-fsanitize=leak)
add_executable(${PROJECT_NAME} ${PROJECT_FILES})

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC include
    PUBLIC lib/inipp
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE ${raylib_LIBRARIES}
)

target_compile_features(
    ${PROJECT_NAME}
    PRIVATE cxx_std_11
    PRIVATE cxx_lambda_init_captures
)
