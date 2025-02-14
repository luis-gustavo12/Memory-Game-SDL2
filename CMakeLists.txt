cmake_minimum_required(VERSION 3.28.3)

project(MEMORY_GAME C)

set(CMAKE_C_STANDARD 11)  # Use C11 standard
set(CMAKE_C_STANDARD_REQUIRED ON)  # Require the specified standard
set(CMAKE_C_EXTENSIONS OFF)  # Disable compiler-specific extensions

# Enable strict compiler warnings
if (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    # MSVC compiler flags
    add_compile_options(/Wall)  # High warning level and treat warnings as errors

    add_definitions(-D_CRT_SECURE_NO_WARNINGS)

else()
    # GCC/Clang compiler flags
    add_compile_options(-Wall -Wextra -Werror)  # Enable all warnings and treat them as errors
endif()

# Add source files
aux_source_directory(source SOURCES)

# Find SDL2 and SDL2_ttf
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES} "source/log.h" "source/log.c")

# Platform-specific configurations
if(WIN32)
    # Link SDL2 libraries
    target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2_ttf::SDL2_ttf SDL2::SDL2main)

    # Add Windows-specific definitions
    target_compile_definitions(${PROJECT_NAME} PRIVATE WINDOWS)

    # Add the -mwindows flag to hide the terminal
    target_link_options(${PROJECT_NAME} PRIVATE -mwindows)

elseif(UNIX)
    # Link SDL2 libraries for Linux/Unix
    target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2_ttf::SDL2_ttf)

    # Add Linux-specific definitions
    target_compile_definitions(${PROJECT_NAME} PRIVATE LINUX)
endif()


