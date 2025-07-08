cmake_minimum_required(VERSION 3.16)
project(Roguelike)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist/bin)

# paths to SDL DLLs
set(SDL_DLLS
        ${CMAKE_SOURCE_DIR}/external/SDL3/SDL3.dll
        ${CMAKE_SOURCE_DIR}/external/SDL3_ttf/SDL3_ttf.dll
        ${CMAKE_SOURCE_DIR}/external/SDL3_image/SDL3_image.dll
)

add_custom_target(copy_sdl_dlls ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SDL_DLLS}
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMENT "Copying SDL3 DLLs to dist/bin"
)

# external dependencies
add_subdirectory(external/SDL3)
add_subdirectory(external/SDL3_ttf)
add_subdirectory(external/SDL3_image)

# build rotex
add_subdirectory(rotex)

# build game
add_subdirectory(game)

add_dependencies(game copy_sdl_dlls)