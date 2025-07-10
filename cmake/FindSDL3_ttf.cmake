find_path(SDL3_ttf_INCLUDE_DIR SDL3_ttf/SDL_ttf.h
        PATHS "${CMAKE_SOURCE_DIR}/external/SDL3_ttf/include"
)

find_library(SDL3_ttf_LIBRARY
        NAMES SDL3_ttf SDL3_ttf.so libSDL3_ttf.a libSDL3_ttf.dll.a SDL3_ttf.dll SDL3_ttf-static
        PATHS "${CMAKE_SOURCE_DIR}/external/SDL3_ttf"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL3_ttf DEFAULT_MSG SDL3_ttf_LIBRARY SDL3_ttf_INCLUDE_DIR)

if (SDL3_ttf_FOUND)
    add_library(SDL3_ttf::SDL3_ttf UNKNOWN IMPORTED)
    set_target_properties(SDL3_ttf::SDL3_ttf PROPERTIES
            IMPORTED_LOCATION "${SDL3_ttf_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${SDL3_ttf_INCLUDE_DIR}"
    )
endif()