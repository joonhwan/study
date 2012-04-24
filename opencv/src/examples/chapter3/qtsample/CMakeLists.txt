CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)

PROJECT(qtsample)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

SET(QT_USE_QTMAIN ON)
INCLUDE(${QT_USE_FILE})

SET(sources
  main.cpp
  ColorIcon.cpp
  MainWindow.cpp
  WCrossSplitter.cpp
  WIntensityProfileWidget.cpp
  WImageViewer.cpp
  WImageViewerPixelItem.cpp
  )

SET(moc_header
  MainWindow.h
  WCrossSplitter.h
  WIntensityProfileWidget.h
  WImageViewer.h
  )

SET(header
  ColorIcon.h
  WImageViewerPixelItem.h
  )

SET(forms
  )

SET(resources
  )

QT4_WRAP_CPP(moc_generated ${moc_header})
QT4_WRAP_UI(forms_generated ${forms})
QT4_ADD_RESOURCES(rc_generated ${resources})

ADD_EXECUTABLE(${PROJECT_NAME} WIN32 MACOSX_BUNDLE
  ${sources}
  ${header}
  ${moc_header}
  ${form}
  ${resource}
  ${moc_generated}
  ${forms_generated}
  ${rc_generated}
  )

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
  ${QT_LIBRARIES}
  image
  property
  algo
  )

set_target_properties(${PROJECT_NAME}
  PROPERTIES
  # COMPILE_DEFINITIONS _AFXDLL,UNICODE
  FOLDER "examples/chapter3"
  )

