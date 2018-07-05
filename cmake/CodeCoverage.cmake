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

if(UNIX AND CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS        "${CMAKE_CXX_FLAGS}        -fprofile-arcs -ftest-coverage")
  set(CMAKE_C_FLAGS          "${CMAKE_CXX_FLAGS}        -fprofile-arcs -ftest-coverage")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif(UNIX AND CMAKE_COMPILER_IS_GNUCXX)

include(Coverage)
include(FindPythonInterp)

if(COVERAGE_USE_COBERTURA)
  SETUP_TARGET_FOR_COVERAGE_COBERTURA(cov ctest coverage)
else(COVERAGE_USE_COBERTURA)
  SETUP_TARGET_FOR_COVERAGE(cov ctest coverage)
endif(COVERAGE_USE_COBERTURA)

######################################################################
### CodeCoverage.cmake ends here
