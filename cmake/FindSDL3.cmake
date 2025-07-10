find_path(SDL3_INCLUDE_DIR SDL3/SDL.h
        PATHS "${CMAKE_SOURCE_DIR}/external/SDL3/include"
)

find_library(SDL3_LIBRARY
        NAMES SDL3 SDL3.so libSDL3.a SDL3.dll libSDL3.dll.a SDL3-static
        PATHS "${CMAKE_SOURCE_DIR}/external/SDL3"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL3 DEFAULT_MSG SDL3_LIBRARY SDL3_INCLUDE_DIR)

if (SDL3_FOUND)
    add_library(SDL3::SDL3 UNKNOWN IMPORTED)
    set_target_properties(SDL3::SDL3 PROPERTIES
            IMPORTED_LOCATION "${SDL3_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${SDL3_INCLUDE_DIR}"
    )
endif()