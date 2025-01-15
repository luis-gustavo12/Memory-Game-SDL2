cmake_minimum_required(VERSION 3.28.3)

project(MEMORY_GAME C)

set(CMAKE_C_STANDARD 11)

file(GLOB SOURCES "source/*.c")

find_package(SDL2 REQUIRED)

find_package(SDL2_ttf REQUIRED)

add_executable( ${PROJECT_NAME} ${SOURCES})



if(WIN32)

    target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2_ttf::SDL2_ttf SDL2::SDL2main)

    target_compile_definitions(${PROJECT_NAME} PRIVATE WINDOWS)
elseif(UNIX)

    target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2_ttf::SDL2_ttf)

    target_compile_definitions(${PROJECT_NAME} PRIVATE LINUX)
endif()