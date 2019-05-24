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

project(dtkCoreLayerTest VERSION ${dtkCore_VERSION})

## ###################################################################
## Input
## ###################################################################

set(${PROJECT_NAME}_HEADERS
  dtkCoreLayerTest
  dtkCoreLayerTest.h
  dtkAbstractCoreConcept
  dtkAbstractCoreConcept.h)

set(${PROJECT_NAME}_SOURCES
  dtkCoreLayerTest.cpp
  dtkAbstractCoreConcept.cpp)

## ###################################################################
## Config file
## ###################################################################

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}Config.h.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.h")

set(${PROJECT_NAME}_HEADERS
  ${${PROJECT_NAME}_HEADERS}
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.h")

## ###################################################################
## Build rules
## ###################################################################

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE dtkLog)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core)
target_link_libraries(${PROJECT_NAME} PUBLIC dtkCore)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
  $<INSTALL_INTERFACE:include>)

## #################################################################
## Install prefix
## #################################################################

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "${PROJECT_NAME} install prefix" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

## #################################################################
## Target properties
## #################################################################

set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_RPATH 0)
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH    "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")

## ###################################################################
## Export header file
## ###################################################################

generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Export.h")
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Export")

set(${PROJECT_NAME}_HEADERS
  ${${PROJECT_NAME}_HEADERS}
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Export"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Export.h")

## ###################################################################
## Install rules - files
## ###################################################################

install(FILES ${${PROJECT_NAME}_HEADERS}
  DESTINATION include/${PROJECT_NAME})

## ###################################################################
## Install rules - targets
## ###################################################################

install(TARGETS ${PROJECT_NAME} EXPORT layer-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

## ###################################################################
## Export configuration
## ###################################################################

include(CMakePackageConfigHelpers)

set(${PROJECT_NAME}_CMAKE_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE
  STRING "install path for ${PROJECT_NAME}Config.cmake")

set(${PROJECT_NAME}_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/${PROJECT_NAME}Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION "${${PROJECT_NAME}_CMAKE_INSTALL_DIR}"
  PATH_VARS ${PROJECT_NAME}_INCLUDE_DIRS)

set(${PROJECT_NAME}_INCLUDE_DIRS ${CMAKE_INSTALL_PREFIX}/include)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/${PROJECT_NAME}Config.cmake.in
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

export(EXPORT layer-targets
  FILE "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")

install(EXPORT layer-targets
  FILE ${PROJECT_NAME}Targets.cmake
  DESTINATION ${${PROJECT_NAME}_CMAKE_INSTALL_DIR})

export(PACKAGE ${PROJECT_NAME})

######################################################################
### CMakeLists.txt ends here
