cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(MyReplWidget)

# Set up the environment
find_package(Qt4 REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(QT_USE_QTMAIN ON)
include(${QT_USE_FILE})

set(sources
  main.cpp mainwindow.cpp ReplWidget.cpp
  )

set(moc_header
  mainwindow.h ReplWidget.h
  )

set(header
  )

set(forms
  mainwindow.ui
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

