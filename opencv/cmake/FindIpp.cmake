# find Matrox Imaging Library depending build environment
# INTEL IPP 7.0

if(BUILD_64)
  if(NOT IPP64_ROOT AND NOT $ENV{IPP64_ROOT} STREQUAL "")
	set(IPP64_ROOT $ENV{IPP64_ROOT})
  endif()
  set(_ipp_INCLUDE_SEARCH_DIRS
	"C:/Program Files (x86)/Intel/ComposerXE-2011/ipp"
	"F:/Program Files/Intel/ComposerXE-2011/ipp"
	"c:/dev/sdk/ipp7-64/ipp"
	${IPP64_ROOT}
	)
else(BUILD_64)
  if(NOT IPP_ROOT AND NOT $ENV{IPP_ROOT} STREQUAL "")
	set(IPP_ROOT $ENV{IPP_ROOT})
  endif()
  set(_ipp_INCLUDE_SEARCH_DIRS
	"c:/Program Files/Intel/ComposerXE-2011/ipp"
	"H:/Program Files/Intel/ComposerXE-2011/ipp"
	"C:/Program Files (x86)/Intel/ComposerXE-2011/ipp"
	"F:/Program Files/Intel/ComposerXE-2011/ipp"
	"c:/dev/sdk/ipp7-32/ipp"
	${IPP_ROOT}
	)
endif(BUILD_64)

if(EXPLICIT_IPP_H_DIR)
  find_path(IPP_H_DIR
	NAMES Ipp.h
	HINTS ${EXPLICIT_IPP_H_DIR}
	PATH_SUFFIXES "include"
	)
else(EXPLICIT_IPP_H_DIR)
  find_path(IPP_H_DIR
	NAMES Ipp.h
	HINTS ${_ipp_INCLUDE_SEARCH_DIRS}
	PATH_SUFFIXES "include"
	)
endif(EXPLICIT_IPP_H_DIR)

if(EXPLICIT_IPP_LIB_DIR)
  find_path(IPP_LIB_DIR
	NAMES ippi.lib 
	HINTS ${EXPLICIT_IPP_LIB_DIR}
	PATH_SUFFIXES ""
	)
else(EXPLICIT_IPP_LIB_DIR)
  if(BUILD_64)
	find_path(IPP_LIB_DIR
	  NAMES ippi.lib 
	  HINTS ${_ipp_INCLUDE_SEARCH_DIRS}
	  PATH_SUFFIXES "lib/intel64"
	  )
	set(IPP_OPENMP_REDIST_DLL "${IPP_H_DIR}/../../redist/intel64/compiler/libiomp5md.dll")
  else(BUILD_64)
	find_path(IPP_LIB_DIR
	  NAMES ippi.lib 
	  HINTS ${_ipp_INCLUDE_SEARCH_DIRS}
	  PATH_SUFFIXES "lib/ia32"
	  )
	set(IPP_OPENMP_REDIST_DLL "${IPP_H_DIR}/../../redist/ia32/compiler/libiomp5md.dll")
  endif(BUILD_64)
endif(EXPLICIT_IPP_LIB_DIR)

if( IPP_H_DIR AND IPP_LIB_DIR )
  set(IPP_FOUND "YES")
  include(FindPackageMessage)
  find_package_message(IPP "Found Ipp at ${IPP_H_DIR}"
	"[${IPP_H_DIR}][${IPP_LIB_DIR}]")
else()
  set(IPP_FOUND "NO")
  if(IPP_FIND_REQUIRED)
	message(FATAL_ERROR "Unable to find IPP library which REQUIRED!")
  else()
	message("Unable to find IPP library!")
  endif()
endif()

set(IPP_USE_FILE ${SIS_SOURCE_DIR}/cmake/UseIpp.cmake)
