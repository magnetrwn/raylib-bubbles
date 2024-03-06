file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.*pp")

# Defines related to I/O, see src/util.cpp
add_definitions(-DCFG_RELATIVE_PATH="bubbles.ini")
add_definitions(-DPATH_BUFFER_SIZE=256)

# Debug defines
add_definitions(-DDEBUG_SHOW_INFO)
#add_definitions(-DDEBUG_MOUSESHOOTER)
add_definitions(-DDEBUG_SPRINKLER)
add_definitions(-DDEBUG_LISSAJOUS)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

target_include_directories(bubbles PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/animation
    ${CMAKE_CURRENT_SOURCE_DIR}/game
    ${CMAKE_CURRENT_SOURCE_DIR}/raylib
    ${CMAKE_CURRENT_SOURCE_DIR}/utility
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${raylib_LIBRARIES} inipp)
