add_library(SDL3_image SHARED IMPORTED GLOBAL)
set_target_properties(SDL3_image PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/external/SDL3_image/SDL3_image.dll"
        IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/external/SDL3_image/SDL3_image.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/external/SDL3_image/include"
)