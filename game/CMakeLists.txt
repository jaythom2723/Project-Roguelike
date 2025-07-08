file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE GAME_HEADERS CONFIGURE_DEPENDS include/*.h)

add_executable(game ${GAME_SOURCES} ${GAME_HEADERS})

target_include_directories(game
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
                ${CMAKE_SOURCE_DIR}/dist/include/rotex
)

target_link_libraries(game
        rotex
        SDL3
        SDL3_ttf
        SDL3_image
)