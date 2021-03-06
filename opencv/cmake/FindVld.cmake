SET(VLD_INSTALL_DIRS
  "C:/Program Files/Visual Leak Detector"
  # more candidate...
  )

SET(VLD_LIBRARY_PATH_SUFFIX "lib/Win32")
IF(${CMAKE_CL_64})
  SET(VLD_LIBRARY_PATH_SUFFIX "lib/Win64")
ENDIF()
message("VLD_LIBRARY_PATH_SUFFIX = ${VLD_LIBRARY_PATH_SUFFIX}.")

# look for the header file
FIND_PATH(VLD_INCLUDE_DIR
  NAMES vld.h
  HINTS ${VLD_INSTALL_DIRS}
  PATH_SUFFIXES include
  )
MARK_AS_ADVANCED(VLD_INCLUDE_DIR)
message("VLD_INCLUDE_DIR = ${VLD_INCLUDE_DIR}")

# look for the library
FIND_LIBRARY(VLD_LIBRARY
  NAMES vld.lib
  HINTS ${VLD_INSTALL_DIRS}
  PATH_SUFFIXES ${VLD_LIBRARY_PATH_SUFFIX}
  )
MARK_AS_ADVANCED(VLD_LIBRARY)


# handle the QUIETLY and REQUIRED arguments and set VLD_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(VLD DEFAULT_MSG VLD_LIBRARY VLD_INCLUDE_DIR)

IF(VLD_FOUND)
  SET(VLD_LIBRARIES ${VLD_LIBRARY})
  SET(VLD_INCLUDE_DIRS ${VLD_INCLUDE_DIR})
ENDIF(VLD_FOUND)
