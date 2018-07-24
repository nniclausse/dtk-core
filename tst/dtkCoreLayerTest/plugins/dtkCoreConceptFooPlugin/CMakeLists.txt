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

project(dtkCoreConceptFooPlugin)

## #################################################################
## Dependencies - external
## #################################################################

find_package(Qt5 COMPONENTS Widgets REQUIRED)

## ###################################################################
## Input
## ###################################################################

set(${PROJECT_NAME}_HEADERS
  dtkCoreConceptFoo.h
  dtkCoreConceptFoo_p.h
  dtkCoreConceptFooPlugin.h
  dtkCoreConceptFooWidget.h)

set(${PROJECT_NAME}_SOURCES
  dtkCoreConceptFoo.cpp
  dtkCoreConceptFoo_p.cpp
  dtkCoreConceptFooPlugin.cpp
  dtkCoreConceptFooWidget.cpp)

## ###################################################################
## Build rules
## ###################################################################

add_definitions(-DQT_PLUGIN)

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

## ###################################################################
## Link rules
## ###################################################################

target_link_libraries(${PROJECT_NAME} dtkCoreLayerTest)
target_link_libraries(${PROJECT_NAME} dtkCore)
target_link_libraries(${PROJECT_NAME} dtkLog)

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

## #################################################################
## Export header file
## #################################################################

generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Export.h")
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Export")

set(${PROJECT_NAME}_HEADERS
  ${${PROJECT_NAME}_HEADERS}
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Export"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Export.h")

## #################################################################
## Install rules
## #################################################################

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION plugins/${DTK_CURRENT_LAYER}
  LIBRARY DESTINATION plugins/${DTK_CURRENT_LAYER}
  ARCHIVE DESTINATION plugins/${DTK_CURRENT_LAYER})

######################################################################
### CMakeLists.txt ends here
