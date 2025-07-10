find_path(SDL3_image_INCLUDE_DIR SDL3_image/SDL_image.h
        PATHS "${CMAKE_SOURCE_DIR}/external/SDL3_image/include"
)

find_library(SDL3_image_LIBRARY
        NAMES SDL3_image SDL3_image.so libSDL3_image.a libSDL3_image.dll.a SDL3_image.dll SDL3_image-static
        PATHS "${CMAKE_SOURCE_DIR}/external/SDL3_image"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL3_image DEFAULT_MSG SDL3_image_LIBRARY SDL3_image_INCLUDE_DIR)

if (SDL3_image_FOUND)
    add_library(SDL3_image::SDL3_image UNKNOWN IMPORTED)
    set_target_properties(SDL3_image::SDL3_image PROPERTIES
            IMPORTED_LOCATION "${SDL3_image_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${SDL3_image_INCLUDE_DIR}"
    )
endif()