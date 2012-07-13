cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(VtkStudy)

message("before VTK_DIR=${VTK_DIR}")

# Set up the environment
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR})
find_package(Qt4 REQUIRED)

message("before VTK_DIR=${VTK_DIR}")
find_package(VTK REQUIRED)
find_package(Vld REQUIRED)

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${VTK_INCLUDE_DIRS}
  )

set(QT_USE_QTMAIN ON)
include(${QT_USE_FILE})

add_subdirectory(cone_test)
add_subdirectory(hello_qvtk)
add_subdirectory(color_mapping)
add_subdirectory(spm_tool)
add_subdirectory(display_quad)
add_subdirectory(cursor)
add_subdirectory(mouse_pick)
add_subdirectory(cell_pick)