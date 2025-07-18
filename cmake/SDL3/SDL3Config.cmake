# SDL cmake project-config input for FindSDL3.txt script

include(FeatureSummary)
set_package_properties(SDL3 PROPERTIES
  URL "https://www.libsdl.org/"
  DESCRIPTION "low level access to audio, keyboard, mouse, joystick, and graphics hardware"
)


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was SDL3Config.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

set(SDL3_FOUND TRUE)
set(_sdl3_framework OFF)

# Find SDL3::Headers
if(NOT TARGET SDL3::Headers)
  include("${CMAKE_CURRENT_LIST_DIR}/SDL3headersTargets.cmake")
  if(NOT CMAKE_VERSION VERSION_LESS "3.25")
    set_property(TARGET SDL3::Headers PROPERTY SYSTEM 0)
  endif()
endif()
set(SDL3_Headers_FOUND TRUE)

# Find SDL3::SDL3-shared
if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/SDL3sharedTargets.cmake")
  include("${CMAKE_CURRENT_LIST_DIR}/SDL3sharedTargets.cmake")
  set(SDL3_SDL3-shared_FOUND TRUE)
endif()

macro(find_sdl3_static_dependencies)

endmacro()

# Find SDL3::SDL3-static
if(_sdl3_framework)
  set(SDL3_SDL3-static_FOUND TRUE)
  find_sdl3_static_dependencies()
  find_package(SDL3-static CONFIG)
  if(SDL3_SDL3-static_FOUND AND SDL3-static_FOUND)
    set(SDL3_SDL3-static_FOUND TRUE)
  endif()
else()
  if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/SDL3staticTargets.cmake")
    set(SDL3_SDL3-static_FOUND TRUE)
    find_sdl3_static_dependencies()
    if(SDL3_SDL3-static_FOUND)
      if(ANDROID OR HAIKU)
        enable_language(CXX)
      endif()
      include("${CMAKE_CURRENT_LIST_DIR}/SDL3staticTargets.cmake")
    endif()
  endif()
endif()

if(ANDROID AND EXISTS "${CMAKE_CURRENT_LIST_DIR}/SDL3jarTargets.cmake")
  include("${CMAKE_CURRENT_LIST_DIR}/SDL3jarTargets.cmake")
  set(SDL3_Jar_FOUND TRUE)
endif()

if(SDL3_SDL3-shared_FOUND OR SDL3_SDL3-static_FOUND)
  set(SDL3_SDL3_FOUND TRUE)
endif()

# Find SDL3::SDL3_test
if(_sdl3_framework)
  find_package(SDL3_test CONFIG)
  if(SDL3_test_FOUND)
    enable_language(OBJC)
    set(SDL3_SDL3_test_FOUND TRUE)
  endif()
else()
  if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/SDL3testTargets.cmake")
    set(SDL3_SDL3_test_FOUND TRUE)

    if(SDL3_SDL3_test_FOUND)
      include("${CMAKE_CURRENT_LIST_DIR}/SDL3testTargets.cmake")
    endif()
  endif()
endif()

if(NOT SDL3_COMPONENTS AND NOT TARGET SDL3::Headers AND NOT TARGET SDL3::SDL3-shared AND NOT TARGET SDL3::SDL3-static)
    set(SDL3_FOUND FALSE)
endif()
check_required_components(SDL3)

function(_sdl_create_target_alias_compat NEW_TARGET TARGET)
  if(CMAKE_VERSION VERSION_LESS "3.18")
    # Aliasing local targets is not supported on CMake < 3.18, so make it global.
    add_library(${NEW_TARGET} INTERFACE IMPORTED)
    set_target_properties(${NEW_TARGET} PROPERTIES INTERFACE_LINK_LIBRARIES "${TARGET}")
  else()
    add_library(${NEW_TARGET} ALIAS ${TARGET})
  endif()
endfunction()

# Make sure SDL3::SDL3 always exists
if(NOT TARGET SDL3::SDL3)
  if(TARGET SDL3::SDL3-shared)
    _sdl_create_target_alias_compat(SDL3::SDL3 SDL3::SDL3-shared)
  elseif(TARGET SDL3::SDL3-static)
    _sdl_create_target_alias_compat(SDL3::SDL3 SDL3::SDL3-static)
  endif()
endif()

set(SDL3_LIBRARIES SDL3::SDL3)
set(SDL3_STATIC_LIBRARIES SDL3::SDL3-static)
set(SDL3_STATIC_PRIVATE_LIBS)

set(SDL3TEST_LIBRARY SDL3::SDL3_test)
