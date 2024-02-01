cmake_minimum_required(VERSION 3.12.0)
project(bubbles)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")

find_package(raylib REQUIRED)

file(GLOB PROJECT_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

#add_compile_definitions(DEBUG)

if(MSVC)
    add_compile_options(/w4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(${PROJECT_NAME} ${PROJECT_FILES})

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC include
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE ${raylib_LIBRARIES}
)

target_compile_features(
    ${PROJECT_NAME}
    PRIVATE cxx_std_14
    PRIVATE cxx_lambda_init_captures
)
