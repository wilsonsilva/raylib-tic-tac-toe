cmake_minimum_required(VERSION 3.26)
project(raylib_tic_tac_toe C)

set(CMAKE_C_STANDARD 11)

# Find raylib
find_package(raylib 4.5 QUIET)

if (NOT raylib_FOUND)  # If there's issue finding raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/4.5.0.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)  # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

add_executable(raylib_tic_tac_toe main.c)
# Link raylib to your project
target_link_libraries(raylib_tic_tac_toe PRIVATE raylib)
