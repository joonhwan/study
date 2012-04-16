PROJECT(algo)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

INCLUDE(${QT_USE_FILE})

SET(sources
  AlgoPropertyManager.cpp
  ColorDetector.cpp
  )

SET(moc_header
  AlgoPropertyManager.h
  ColorDetector.h
  )

SET(header
  )

SET(forms
  )

SET(resources
  )

QT4_WRAP_CPP(moc_generated ${moc_header})
QT4_WRAP_UI(forms_generated ${forms})
QT4_ADD_RESOURCES(rc_generated ${resources})

ADD_LIBRARY(${PROJECT_NAME} STATIC
  ${sources}
  ${header}
  ${moc_header}
  ${form}
  ${resource}
  ${moc_generated}
  ${forms_generated}
  ${rc_generated}
  )

set_target_properties(${PROJECT_NAME}
  PROPERTIES
  # COMPILE_DEFINITIONS _AFXDLL,UNICODE
  FOLDER "common"
  )

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
  image
  property
  )
