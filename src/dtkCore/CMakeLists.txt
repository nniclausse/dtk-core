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
  dtkCoreApplication_p
  dtkCoreApplication_p.h
  dtkCoreApplication
  dtkCoreApplication.h
  dtkCoreIOCompressor
  dtkCoreIOCompressor.h
  dtkCoreLayerManager
  dtkCoreLayerManager.h
  dtkCoreMetaContainerSequential
  dtkCoreMetaContainerSequential.h
  dtkCoreMetaContainerSequential.tpp
  dtkCoreMetaContainerSequentialHandler
  dtkCoreMetaContainerSequentialHandler.h
  dtkCoreMetaContainerSequentialHandler.tpp
  dtkCoreMetaType
  dtkCoreMetaType.h
  dtkCoreMetaType.tpp
  dtkCoreObjectManager
  dtkCoreObjectManager.h
  dtkCoreParameters
  dtkCoreParameters.h
  dtkCoreParameter
  dtkCoreParameter.h
  dtkCoreParameter.tpp
  dtkCoreParameterInList
  dtkCoreParameterInList.h
  dtkCoreParameterInList.tpp
  dtkCoreParameterInListStringList
  dtkCoreParameterInListStringList.h
  dtkCoreParameterNumeric
  dtkCoreParameterNumeric.h
  dtkCoreParameterNumeric.tpp
  dtkCoreParameterPath
  dtkCoreParameterPath.h
  dtkCoreParameterRange
  dtkCoreParameterRange.h
  dtkCoreParameterRange.tpp
  dtkCoreParameterSimple
  dtkCoreParameterSimple.h
  dtkCoreParameterSimple.tpp
  dtkCoreParameterObject
  dtkCoreParameterObject.h
  dtkCoreParameterInListObject
  dtkCoreParameterInListObject.h
  dtkCoreParameterInListStringListObject
  dtkCoreParameterInListStringListObject.h
  dtkCoreParameterPathObject
  dtkCoreParameterPathObject.h
  dtkCoreParameterNumericObject
  dtkCoreParameterNumericObject.h
  dtkCoreParameterRangeObject
  dtkCoreParameterRangeObject.h
  dtkCoreParameterSimpleObject
  dtkCoreParameterSimpleObject.h
  dtkCoreParameterCollection
  dtkCoreParameterCollection.h
  dtkCorePlugin
  dtkCorePlugin.h
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
  dtkCorePluginWidgetManager
  dtkCorePluginWidgetManager.h
  dtkCoreSettings
  dtkCoreSettings.h
  dtkCoreTypeTraits
  dtkCoreTypeTraits.h)

set(${PROJECT_NAME}_SOURCES
  dtkCoreApplication.cpp
  dtkCoreIOCompressor.cpp
  dtkCoreLayerManager.cpp
  dtkCoreMetaType.cpp
  dtkCoreObjectManager.cpp
  dtkCoreMetaContainerSequential.cpp
  dtkCoreParameter.cpp
  dtkCoreParameterInList.cpp
  dtkCoreParameterInListStringList.cpp
  dtkCoreParameterNumeric.cpp
  dtkCoreParameterPath.cpp
  dtkCoreParameterRange.cpp
  dtkCoreParameterSimple.cpp
  dtkCoreParameterObject.cpp
  dtkCoreParameterInListObject.cpp
  dtkCoreParameterInListStringListObject.cpp
  dtkCoreParameterPathObject.cpp
  dtkCoreParameterNumericObject.cpp
  dtkCoreParameterRangeObject.cpp
  dtkCoreParameterSimpleObject.cpp
  dtkCoreParameterCollection.cpp
  dtkCorePlugin.cpp
  dtkCorePluginFactory_p.cpp
  dtkCorePluginFactoryRecorder.cpp
  dtkCorePluginManagerHandler.cpp
  dtkCorePluginManagerRecorder.cpp
  dtkCorePluginWidgetManager.cpp)

## ###################################################################
## Config file
## ###################################################################

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}Config.h.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.h")

set(${PROJECT_NAME}_HEADERS
  ${${PROJECT_NAME}_HEADERS}
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.h")

set(layer_BINARY_DIR "${PROJECT_BINARY_DIR}/..")

## #################################################################
## Build rules
## #################################################################

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

target_link_libraries(${PROJECT_NAME} PUBLIC dtkLog)

#if(DTK_HAVE_ZLIB)
  target_link_libraries(${PROJECT_NAME} PRIVATE ZLIB_INTERFACE)
#endif(DTK_HAVE_ZLIB)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Qml)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${layer_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
  $<BUILD_INTERFACE:${layer_BINARY_DIR}>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
  $<INSTALL_INTERFACE:include>)

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
## Install rules - files
## ###################################################################

install(FILES ${${PROJECT_NAME}_HEADERS}
  DESTINATION include/${PROJECT_NAME})

## ###################################################################
## Install rules - targets
## ###################################################################

install(TARGETS ${PROJECT_NAME} EXPORT ${LAYER_TARGETS}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

######################################################################
### CMakeLists.txt ends here
