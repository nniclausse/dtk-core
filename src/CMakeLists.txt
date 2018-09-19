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

add_subdirectory(dtkCore)
add_subdirectory(dtkCoreRuntime)

## #################################################################
## Target definition
## #################################################################

set(DTKCORE_TARGETS)

set(DTKCORE_TARGETS ${DTKCORE_TARGETS} dtkCore)
set(DTKCORE_TARGETS ${DTKCORE_TARGETS} dtkCoreRuntime)

## #################################################################
## Target export
## #################################################################

export(TARGETS ${DTKCORE_TARGETS} FILE "${CMAKE_BINARY_DIR}/dtkCoreDepends.cmake")

######################################################################
### CMakeLists.txt ends here
