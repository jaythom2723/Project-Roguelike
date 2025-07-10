file(GLOB_RECURSE ROTEX_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE ROTEX_HEADERS CONFIGURE_DEPENDS include/*.h)

add_library(rotex SHARED ${ROTEX_SOURCES})

target_include_directories(rotex
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC ${CMAKE_SOURCE_DIR}/external/SDL3/include
        PUBLIC ${CMAKE_SOURCE_DIR}/external/SDL3_ttf/include
        PUBLIC ${CMAKE_SOURCE_DIR}/external/SDL3_image/include
        PUBLIC ${CMAKE_SOURCE_DIR}/external/lua/include
        PUBLIC ${CMAKE_SOURCE_DIR}/external/toml++/include
)

target_compile_definitions(rotex
    PRIVATE ROTEX_EXPORTS
)

target_link_libraries(rotex
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf
        LUA::LUA
)

add_custom_target(copy_rotex_headers ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/dist/include/rotex
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${CMAKE_SOURCE_DIR}/dist/include/rotex
        COMMENT "Copying rotex headers to dist/include/rotex"
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_SOURCE_DIR}/dist/include/rotex
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

add_dependencies(rotex copy_rotex_headers)
