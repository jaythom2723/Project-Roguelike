cmake_minimum_required(VERSION 3.16)
project(Roguelike)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist/bin)

# external dependencies
find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(LUA REQUIRED)

add_custom_target(copy_dlls ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/external/SDL3/SDL3.dll
            ${CMAKE_SOURCE_DIR}/external/SDL3_ttf/SDL3_ttf.dll
            ${CMAKE_SOURCE_DIR}/external/SDL3_image/SDL3_image.dll
            ${CMAKE_SOURCE_DIR}/external/lua/lua54.dll
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMENT "Copying SDL3 DLLs to dist/bin"
)

# build rotex
add_subdirectory(rotex)

# build game
add_subdirectory(game)

add_dependencies(game copy_dlls rotex)