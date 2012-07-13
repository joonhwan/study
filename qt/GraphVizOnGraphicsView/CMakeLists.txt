cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(graphviz_test)

# Set up the environment
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR};${CMAKE_MODULE_PATH})
set(QTDIR "c:/qt/4.8.1-x86")
find_package(Qt4 REQUIRED)
find_package(GraphViz REQUIRED)

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${GraphViz_INCLUDE_DIR}
  )

# set(QT_USE_QTMAIN ON)
include(${QT_USE_FILE})

set(sources
  main.cpp
  GVGraph.cpp
  WGraphicsArrowItem.cpp
  WGraphicsUtil.cpp
  )

set(moc_header
  )

set(header
  GVGraph.h
  WGraphicsArrowItem.h
  WGraphicsUtil.h
  )

set(forms
  )

set(resources
  )

qt4_wrap_cpp(moc_generated ${moc_header})
qt4_wrap_ui(forms_generated ${forms})
qt4_add_resources(rc_generated ${resources})

add_executable(${PROJECT_NAME} MACOSX_BUNDLE
  ${sources}
  ${header}
  ${moc_header}
  ${form}
  ${resource}
  ${moc_generated}
  ${forms_generated}
  ${rc_generated}
  )

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  ${GraphViz_LIBRARIES}
  )
