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
set(${PROJECT_NAME}_VERSION_MINOR 1)
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

set(CMAKE_INSTALL_RPATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)

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
  set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "${PROJECT_NAME} install prefix" FORCE)
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

find_package(Qt5 REQUIRED COMPONENTS Core Test WebSockets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(DTK_HAVE_ZLIB "NO")
find_package(ZLIB QUIET)
if(ZLIB_FOUND)
  include_directories(${ZLIB_INCLUDE_DIRS})
  set(DTK_HAVE_ZLIB "YES")
endif(ZLIB_FOUND)

find_package(dtkLog REQUIRED)
include_directories(${dtkLog_INCLUDE_DIRS})

## #################################################################
## Dependencies - internal
## #################################################################

include_directories(${CMAKE_BINARY_DIR})
include_directories(${CMAKE_BINARY_DIR}/src)
include_directories(${CMAKE_BINARY_DIR}/src/dtkCore)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/dtkCore)

## ###################################################################
## Input
## ###################################################################

add_subdirectory(src)
add_subdirectory(tst)

## ###################################################################
## Exporting
## ###################################################################

export(PACKAGE ${PROJECT_NAME})

configure_file(${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
  "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake" @ONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.install.cmake.in
  "${CMAKE_BINARY_DIR}/install/${PROJECT_NAME}Config.cmake" @ONLY)

configure_file(${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}ConfigVersion.cmake.in
  "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake" @ONLY)

install(FILES
  "${CMAKE_BINARY_DIR}/install/${PROJECT_NAME}Config.cmake"
  "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION  ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

install(EXPORT ${PROJECT_NAME}Depends DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

## ###################################################################
## Beautifying
## ###################################################################

mark_as_advanced(${PROJECT_NAME}_VERSION_MAJOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_MINOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_BUILD)

mark_as_advanced(Qt5_DIR)
mark_as_advanced(Qt5Core_DIR)
mark_as_advanced(Qt5Test_DIR)

mark_as_advanced(CMAKE_AR)
mark_as_advanced(CMAKE_OSX_ARCHITECTURES)
mark_as_advanced(CMAKE_OSX_DEPLOYMENT_TARGET)
mark_as_advanced(CMAKE_OSX_SYSROOT)

## ###################################################################
## Packaging
## ###################################################################

include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT_NAME}_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${${PROJECT_NAME}_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${${PROJECT_NAME}_VERSION_PATCH}")

include(CPack)

######################################################################
### CMakeLists.txt ends here
