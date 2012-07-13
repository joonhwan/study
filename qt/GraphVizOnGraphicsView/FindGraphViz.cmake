# Copyright (C) 2007-2009 LuaDist.
# Created by Peter Kapec <kapecp@gmail.com>
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the COPYRIGHT file distributed with LuaDist.
# Note:
# Searching headers and libraries is very simple and is NOT as powerful as scripts
# distributed with CMake, because LuaDist defines directories to search for.
# Everyone is encouraged to contact the author with improvements. Maybe this file
# becomes part of CMake distribution sometimes.

# - Find GraphViz
# Find the native GraphViz headers and libraries.
#
# GraphViz_INCLUDE_DIRS - where to find m_apm.h, etc.
# GraphViz_LIBRARIES - List of libraries when using GraphViz.
# GRAPHVIZ_FOUND - True if GraphViz found.

set(GraphViz_INSTALL_DIRS
  "$ENV{GRAPHVIZ_DIR}"
  )

# Look for the header file.
find_path(GraphViz_INCLUDE_DIR
  NAMES graphviz/graph.h
  HINTS ${GraphViz_INSTALL_DIRS}
  PATH_SUFFIXES "include"
  )

# Look for the library.
find_library(GraphViz_gvc_LIBRARY
  NAMES gvc
  HINTS ${GraphViz_INSTALL_DIRS}
  PATH_SUFFIXES "lib/release/lib"
  )

find_library(GraphViz_graph_LIBRARY
  NAMES graph
  HINTS ${GraphViz_INSTALL_DIRS}
  PATH_SUFFIXES "lib/release/lib"
  )
find_library(GraphViz_cdt_LIBRARY
  NAMES cdt
  HINTS ${GraphViz_INSTALL_DIRS}
  PATH_SUFFIXES "lib/release/lib"
  )
find_library(GraphViz_pathplan_LIBRARY
  NAMES pathplan
  HINTS ${GraphViz_INSTALL_DIRS}
  PATH_SUFFIXES "lib/release/lib"
  )

set(GraphViz_LIBRARY ${GraphViz_gvc_LIBRARY} ${GraphViz_graph_LIBRARY} ${GraphViz_cdt_LIBRARY} ${GraphViz_pathplan_LIBRARY})

# Handle the QUIETLY and REQUIRED arguments and set GraphViz_FOUND to TRUE if all listed variables are TRUE.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GraphViz DEFAULT_MSG GraphViz_LIBRARY GraphViz_INCLUDE_DIR)

# Copy the results to the output variables.
if(GRAPHVIZ_FOUND)
  set(GraphViz_LIBRARIES ${GraphViz_LIBRARY})
  set(GraphViz_INCLUDE_DIRS ${GraphViz_INCLUDE_DIR})
else(GRAPHVIZ_FOUND)
  set(GraphViz_LIBRARIES)
  set(GraphViz_INCLUDE_DIRS)
endif(GRAPHVIZ_FOUND)

mark_as_advanced(GraphViz_INCLUDE_DIRS GraphViz_LIBRARIES)


