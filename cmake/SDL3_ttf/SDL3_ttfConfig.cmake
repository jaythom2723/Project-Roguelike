# sdl3_ttf cmake project-config input for FindSDL3.txt script

include(FeatureSummary)
set_package_properties(SDL3_ttf PROPERTIES
    URL "https://www.libsdl.org/projects/SDL_ttf/"
    DESCRIPTION "Support for TrueType (.ttf) font files with Simple Directmedia Layer"
)

set(SDL3_ttf_FOUND ON)

set(SDLTTF_VENDORED  ON)

set(SDLTTF_PLUTOSVG TRUE)
set(SDLTTF_HARFBUZZ TRUE)
set(SDLTTF_FREETYPE TRUE)

set(SDLTTF_HARFBUZZ_REQUIRED_VERSION    2.3.1)
set(SDLTTF_SDL3_REQUIRED_VERSION        3.1.5)

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/SDL3_ttf-shared-targets.cmake")
    include("${CMAKE_CURRENT_LIST_DIR}/SDL3_ttf-shared-targets.cmake")
endif()

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/SDL3_ttf-static-targets.cmake")
    if(SDLTTF_VENDORED)
        if(SDLTTF_HARFBUZZ AND NOT MSVC)
            find_package(Threads)
        endif()
        include(CheckLanguage)
        check_language(CXX)
        if(NOT CMAKE_CXX_COMPILER AND NOT _sdl3ttf_nowarning)
            message(WARNING "CXX language not enabled. Linking to SDL3_ttf::SDL3_ttf-static might fail.")
        endif()
    else()
        set(_sdl_cmake_module_path "${CMAKE_MODULE_PATH}")
        list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

        include(CMakeFindDependencyMacro)
        include(PkgConfigHelper)

        if(SDLTTF_FREETYPE AND NOT Freetype::Freetype)
            find_dependency(Freetype)
        endif()

        if(SDLTTF_HARFBUZZ AND NOT harfbuzz::harfbuzz)
            list(APPEND harfbuzz_ROOT "${CMAKE_CURRENT_LIST_DIR}")
            find_dependency(harfbuzz ${SDLTTF_HARFBUZZ_REQUIRED_VERSION})
        endif()

        if(SDLTTF_PLUTOSVG AND NOT plutosvg::plutosvg)
            list(APPEND plutosvg_ROOT "${CMAKE_CURRENT_LIST_DIR}")
            find_dependency(plutosvg)
        endif()

        set(CMAKE_MODULE_PATH "${_sdl_cmake_module_path}")
        unset(_sdl_cmake_module_path)
    endif()

    include("${CMAKE_CURRENT_LIST_DIR}/SDL3_ttf-static-targets.cmake")
endif()

function(_sdl_create_target_alias_compat NEW_TARGET TARGET)
    if(CMAKE_VERSION VERSION_LESS "3.18")
        # Aliasing local targets is not supported on CMake < 3.18, so make it global.
        add_library(${NEW_TARGET} INTERFACE IMPORTED)
        set_target_properties(${NEW_TARGET} PROPERTIES INTERFACE_LINK_LIBRARIES "${TARGET}")
    else()
        add_library(${NEW_TARGET} ALIAS ${TARGET})
    endif()
endfunction()

# Make sure SDL3_ttf::SDL3_ttf always exists
if(NOT TARGET SDL3_ttf::SDL3_ttf)
    if(TARGET SDL3_ttf::SDL3_ttf-shared)
        _sdl_create_target_alias_compat(SDL3_ttf::SDL3_ttf SDL3_ttf::SDL3_ttf-shared)
    else()
        _sdl_create_target_alias_compat(SDL3_ttf::SDL3_ttf SDL3_ttf::SDL3_ttf-static)
    endif()
endif()

