add_library(SDL3_ttf SHARED IMPORTED GLOBAL)
set_target_properties(SDL3_ttf PROPERTIES
        IMPORTED_LOCATIONS "${CMAKE_SOURCE_DIR}/external/SDL3_ttf/SDL3_ttf.dll"
        IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/external/SDL3_ttf/SDL3_ttf.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/external/SDL3_ttf/include"
)