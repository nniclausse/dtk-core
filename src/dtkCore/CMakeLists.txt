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

project(dtkCore VERSION ${dtkCore_VERSION})

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkCore
  dtkCoreLayerManager
  dtkCoreLayerManager.h
  dtkCoreMetaType
  dtkCoreMetaType.h
  dtkCoreMetaType.tpp
  dtkCoreObjectManager
  dtkCoreObjectManager.h
  dtkCorePluginBase
  dtkCorePluginBase.h
  dtkCorePluginFactory
  dtkCorePluginFactory.h
  dtkCorePluginFactory.tpp
  dtkCorePluginFactory_p.h
  dtkCorePluginFactoryRecorder
  dtkCorePluginFactoryRecorder.h
  dtkCorePluginManager
  dtkCorePluginManager.h
  dtkCorePluginManager.tpp
  dtkCorePluginManagerHandler
  dtkCorePluginManagerHandler.h
  dtkCorePluginManagerRecorder
  dtkCorePluginManagerRecorder.h
  dtkCoreSettings
  dtkCoreSettings.h)

set(${PROJECT_NAME}_SOURCES
  dtkCoreLayerManager.cpp
  dtkCoreMetaType.cpp
  dtkCoreObjectManager.cpp
  dtkCorePluginFactory_p.cpp
  dtkCorePluginFactoryRecorder.cpp
  dtkCorePluginManagerHandler.cpp
  dtkCorePluginManagerRecorder.cpp)

if(DTK_HAVE_ZLIB)
  set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
    dtkCoreIOCompressor
    dtkCoreIOCompressor.h)

  set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
    dtkCoreIOCompressor.cpp)
endif(DTK_HAVE_ZLIB)

## #################################################################
## Build rules
## #################################################################

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

target_link_libraries(${PROJECT_NAME} Qt5::Core)

if(DTK_HAVE_ZLIB)
  target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES})
endif(DTK_HAVE_ZLIB)

## #################################################################
## Target properties
## #################################################################

set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_RPATH 0)
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH    "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION   ${${PROJECT_NAME}_VERSION}
                                                 SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR})

## #################################################################
## Export header file
## #################################################################

generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export")
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export.h")

set(${PROJECT_NAME}_HEADERS
  ${${PROJECT_NAME}_HEADERS}
  "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export"
  "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export.h")

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
    COMPONENT core)

## ###################################################################
## Install rules - targets
## ###################################################################

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT core
         EXPORT dtkCoreDepends)

######################################################################
### CMakeLists.txt ends here
