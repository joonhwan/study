
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(QActiveXTester)

# Set up the environment
find_package(Qt4 REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(QT_USE_QTMAIN ON)
set(QT_USE_QAXCONTAINER ON)
include(${QT_USE_FILE})

set(sources
  main.cpp
  excel.cpp
  WDispatchDriver.cpp
  )

set(moc_header
  )

set(header
  excel.h
  WDispatchDriver.h
  )

set(forms
  )

set(resources
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
  ${QT_LIBRARIES}
  )

