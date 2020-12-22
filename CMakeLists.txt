## Version: $Id$
##
######################################################################
##
### Commentary:
##
######################################################################
##
### Change Log:
##
######################################################################
##
### Code:

cmake_minimum_required(VERSION 3.6.0)

######################################################################

project(dtkCore)

## ###################################################################
## cmake modules folder
## ###################################################################

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

## ###################################################################
## Version setup
## ###################################################################

set(${PROJECT_NAME}_VERSION_MAJOR 2)
set(${PROJECT_NAME}_VERSION_MINOR 9)
set(${PROJECT_NAME}_VERSION_PATCH 0)
set(${PROJECT_NAME}_VERSION
  ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH})

## ###################################################################
## Output directory setup
## ###################################################################

include(GNUInstallDirs)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

## ###################################################################
## Default build type (RelWithDebInfo)
## ###################################################################

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

## #################################################################
## Install prefix
## #################################################################

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  if (DEFINED ENV{CONDA_PREFIX})
    set(CMAKE_INSTALL_LIBDIR "lib" CACHE PATH "${PROJECT_NAME} libdir" FORCE)
    set(CMAKE_INSTALL_PREFIX "$ENV{CONDA_PREFIX}" CACHE PATH "${PROJECT_NAME} install prefix" FORCE)
  else()
    set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "${PROJECT_NAME} install prefix" FORCE)
  endif()
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

## #################################################################
## Generate compilation database
## #################################################################

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

## #################################################################
## Build setup
## #################################################################

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_SKIP_BUILD_RPATH  FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)

if("${isSystemDir}" STREQUAL "-1")
   set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
endif("${isSystemDir}" STREQUAL "-1")

## ###################################################################
## Test setup
## ###################################################################

include(CTest)
enable_testing()

## ###################################################################
## Code coverage setup
## ###################################################################

option(ENABLE_COVERAGE        "enable coverage report"        false)
option(COVERAGE_USE_COBERTURA "use cobertura coverage format" false)

if(ENABLE_COVERAGE)
  include(CodeCoverage)
endif(ENABLE_COVERAGE)

## ###################################################################
## Dependencies - cmake
## ###################################################################

include(GenerateExportHeader)

## #################################################################
## Dependencies - external
## #################################################################

find_package(Qt5 REQUIRED COMPONENTS Core Test Widgets Gui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(DTK_HAVE_ZLIB "NO")
find_package(ZLIB QUIET)
if(ZLIB_FOUND)
  set(DTK_HAVE_ZLIB "YES")
endif(ZLIB_FOUND)

if(NOT TARGET dtkLog)
  find_package(dtkLog REQUIRED)
endif()

## ###################################################################
## Input
## ###################################################################

add_subdirectory(src)
add_subdirectory(tst)

## ###################################################################
## Export configuration
## ###################################################################

include(CMakePackageConfigHelpers)

set(${PROJECT_NAME}_CMAKE_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE
  STRING "install path for ${PROJECT_NAME}Config.cmake")

set(${PROJECT_NAME}_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src)
configure_package_config_file(cmake/${PROJECT_NAME}Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION "${${PROJECT_NAME}_CMAKE_INSTALL_DIR}"
  PATH_VARS ${PROJECT_NAME}_INCLUDE_DIRS)

set(${PROJECT_NAME}_INCLUDE_DIRS ${CMAKE_INSTALL_PREFIX}/include)
configure_package_config_file(cmake/${PROJECT_NAME}Config.cmake.in
  ${PROJECT_BINARY_DIR}/to_install/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION "${${PROJECT_NAME}_CMAKE_INSTALL_DIR}"
  PATH_VARS ${PROJECT_NAME}_INCLUDE_DIRS)

write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  VERSION ${${PROJECT_NAME}_VERSION}
  COMPATIBILITY AnyNewerVersion)

## ###################################################################
## Exporting
## ###################################################################

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/to_install/${PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  DESTINATION ${${PROJECT_NAME}_CMAKE_INSTALL_DIR})

install(EXPORT layer-targets
  FILE ${PROJECT_NAME}Targets.cmake
  DESTINATION ${${PROJECT_NAME}_CMAKE_INSTALL_DIR})

export(PACKAGE ${PROJECT_NAME})

## ###################################################################
## Beautifying
## ###################################################################

mark_as_advanced(${PROJECT_NAME}_VERSION_MAJOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_MINOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_BUILD)

mark_as_advanced(${PROJECT_NAME}_CMAKE_INSTALL_DIR)

mark_as_advanced(Qt5_DIR)
mark_as_advanced(Qt5Core_DIR)
mark_as_advanced(Qt5Widgets_DIR)
mark_as_advanced(Qt5Gui_DIR)
mark_as_advanced(Qt5Test_DIR)

mark_as_advanced(CMAKE_AR)
mark_as_advanced(CMAKE_INSTALL_PREFIX)
mark_as_advanced(CMAKE_OSX_ARCHITECTURES)
mark_as_advanced(CMAKE_OSX_DEPLOYMENT_TARGET)
mark_as_advanced(CMAKE_OSX_SYSROOT)

######################################################################
### CMakeLists.txt ends here
