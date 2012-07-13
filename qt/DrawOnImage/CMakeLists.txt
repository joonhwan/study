cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(drawOnImage)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR})

# Set up the environment
find_package(Qt4 REQUIRED)
find_package(Vld REQUIRED) # visual leak detector library

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(QT_USE_QTMAIN ON)
include(${QT_USE_FILE})
include(${VLD_USE_FILE})

set(sources
  main.cpp
  DrawOnImageWindow.cpp
  )

set(moc_header
  DrawOnImageWindow.h
  )

set(header
  )

set(forms
  )

set(resources
  res.qrc
  )

qt4_wrap_cpp(moc_generated ${moc_header})
qt4_wrap_ui(forms_generated ${forms})
qt4_add_resources(rc_generated ${resources})

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE
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
  msvcrtd.lib
  ${QT_LIBRARIES}
  )
