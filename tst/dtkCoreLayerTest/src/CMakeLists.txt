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

project(dtkCoreLayerTest)

## #################################################################
## Install prefix
## #################################################################

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "${PROJECT_NAME} install prefix" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

## ###################################################################
## Exporting
## ###################################################################

export(PACKAGE ${PROJECT_NAME})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/${PROJECT_NAME}Config.cmake.in
  "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake" @ONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/${PROJECT_NAME}Config.install.cmake.in
  "${CMAKE_BINARY_DIR}/install/${PROJECT_NAME}Config.cmake" @ONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/${PROJECT_NAME}ConfigVersion.cmake.in
  "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake" @ONLY)

install(FILES
  "${CMAKE_BINARY_DIR}/install/${PROJECT_NAME}Config.cmake"
  "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION  ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

install(EXPORT ${PROJECT_NAME}Depends DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

## ###################################################################
## Input
## ###################################################################

set(${PROJECT_NAME}_HEADERS
  dtkCoreLayerTest
  dtkCoreLayerTest.h
  dtkCoreLayerTestSettings
  dtkCoreLayerTestSettings.h
  dtkAbstractCoreConcept
  dtkAbstractCoreConcept.h)

set(${PROJECT_NAME}_SOURCES
  dtkCoreLayerTest.cpp
  dtkCoreLayerTestSettings.cpp
  dtkAbstractCoreConcept.cpp)

## #################################################################
## Dependencies - internal
## #################################################################

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

message ("${CMAKE_CURRENT_BINARY_DIR}")
message ("${CMAKE_BINARY_DIR}")

## ###################################################################
## Build rules
## ###################################################################

qt5_add_RESOURCES(${PROJECT_NAME}_SOURCES_QRC ${${PROJECT_NAME}_RESOURCES})

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

## ###################################################################
## Link rules
## ###################################################################

target_link_libraries(${PROJECT_NAME} Qt5::Core)

target_link_libraries(${PROJECT_NAME} dtkCore)
target_link_libraries(${PROJECT_NAME} dtkLog)

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
## Config file
## ###################################################################

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}Config.h.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.h")

set(${PROJECT_NAME}_HEADERS
  ${${PROJECT_NAME}_HEADERS}
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.h")

## ###################################################################
## Install rules - files
## ###################################################################

install(FILES ${${PROJECT_NAME}_HEADERS}
  DESTINATION include/${PROJECT_NAME}
    COMPONENT core-layer-test)

## ###################################################################
## Install rules - targets
## ###################################################################

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT core-layer-test
         EXPORT dtkCoreLayerTestDepends)

## #################################################################
## Target export
## #################################################################

export(TARGETS ${PROJECT_NAME} FILE "${CMAKE_BINARY_DIR}/dtkCoreLayerTestDepends.cmake")

######################################################################
### CMakeLists.txt ends here
