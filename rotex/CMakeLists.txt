file(GLOB_RECURSE ROTEX_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE ROTEX_HEADERS CONFIGURE_DEPENDS include/*.h)

add_library(rotex SHARED ${ROTEX_SOURCES})

target_include_directories(rotex
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC ${CMAKE_SOURCE_DIR}/external/SDL3/include
        PUBLIC ${CMAKE_SOURCE_DIR}/external/SDL3_ttf/include
        PUBLIC ${CMAKE_SOURCE_DIR}/external/SDL3_image/include
)

target_compile_definitions(rotex
    PRIVATE ROTEX_EXPORTS
)

target_link_libraries(rotex
        SDL3
        SDL3_image
        SDL3_ttf
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_SOURCE_DIR}/dist/include/rotex
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
