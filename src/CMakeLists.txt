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

set(layer_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(dtkCore)
add_subdirectory(dtkCoreRuntime)

## #################################################################
## Target export
## #################################################################

export(EXPORT layer-targets-dtkCore
  FILE "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")

######################################################################
### CMakeLists.txt ends here
