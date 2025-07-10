find_path(LUA_INCLUDE_DIR lua.h
        PATHS "${CMAKE_SOURCE_DIR}/external/lua/include"
)

find_library(LUA_LIBRARY
        NAMES lua54 lua54.so liblua54.a lua54.dll liblua54.dll.a lua-static
        PATHS "${CMAKE_SOURCE_DIR}/external/lua"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LUA DEFAULT_MSG LUA_LIBRARY LUA_INCLUDE_DIR)

if (LUA_FOUND)
    add_library(LUA::LUA UNKNOWN IMPORTED)
    set_target_properties(LUA::LUA PROPERTIES
            IMPORTED_LOCATION "${LUA_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${LUA_INCLUDE_DIR}"
    )
endif()