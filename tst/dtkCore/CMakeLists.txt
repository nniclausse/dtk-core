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

project(dtkCoreTests)

## ###################################################################
## Build tree setup
## ###################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

## ###################################################################
## Input
## ###################################################################

set(${PROJECT_NAME}_HEADERS
  dtkCoreAsKeyValueRangeTest.h
  dtkCoreIOCompressorTest.h
  dtkCoreMetaContainerSequentialTest.h
  dtkCoreMetaContainerSequentialTest.tpp
  dtkCoreMetaTypeTest.h
  dtkCoreParameterTest.h
  dtkCorePluginFactoryTest.h)

set(${PROJECT_NAME}_SOURCES
  dtkCoreAsKeyValueRangeTest.cpp
  dtkCoreIOCompressorTest.cpp
  dtkCoreMetaContainerSequentialTest.cpp
  dtkCoreMetaTypeTest.cpp
  dtkCoreParameterTest.cpp
  dtkCorePluginFactoryTest.cpp)

set(${PROJECT_NAME}_SOURCES_QRC dtkCore.qrc)

set_property( SOURCE qrc_dtkCore.cpp PROPERTY SKIP_AUTOMOC ON)
## ###################################################################
## Input - introspected
## ###################################################################

create_test_sourcelist(
  ${PROJECT_NAME}_SOURCES_TST
  ${PROJECT_NAME}.cpp
  ${${PROJECT_NAME}_SOURCES})

## ###################################################################
## Build rules
## ###################################################################
qt5_add_resources(${PROJECT_NAME}_SOURCES_RCC ${${PROJECT_NAME}_SOURCES_QRC})

add_executable(${PROJECT_NAME}
  ${${PROJECT_NAME}_SOURCES_TST}
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_SOURCES_RCC}
)

## ###################################################################
## Link rules
## ###################################################################

target_link_libraries(${PROJECT_NAME} dtkCore)

target_link_libraries(${PROJECT_NAME} dtkCoreLayerTest)
target_link_libraries(${PROJECT_NAME} dtkCoreConceptFooPlugin)

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Qml)
target_link_libraries(${PROJECT_NAME} Qt5::Test)

## ###################################################################
## Test rules
## ###################################################################

add_test(dtkCoreAsKeyValueRangeTest         ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} dtkCoreAsKeyValueRangeTest)
add_test(dtkCoreIOCompressorTest            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} dtkCoreIOCompressorTest)
add_test(dtkCoreMetaTypeTest                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} dtkCoreMetaTypeTest)
add_test(dtkCoreMetaContainerSequentialTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} dtkCoreMetaContainerSequentialTest)
add_test(dtkCoreParameterTest               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} dtkCoreParameterTest)
add_test(dtkCorePluginFactoryTest           ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} dtkCorePluginFactoryTest)

######################################################################
### CMakeLists.txt ends here
