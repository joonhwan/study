PROJECT(property)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

INCLUDE(${QT_USE_FILE})

SET(sources
  PropertyManager.cpp
  PropertySystem.cpp
  PlainColorProperty.cpp
  SliderSpinValueProperty.cpp
  )

SET(moc_header
  PropertyManager.h
  PropertySystem.h
  PlainColorProperty.h
  SliderSpinValueProperty.h
  )

SET(header
  PropertyBase.h
  RangedProperty.h
  SimpleProperty.h
  SliderSpinEditor.h
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
  FOLDER "framework"
  )

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
  ${QT_LIBRARIES}
  qtpropertybrowser
  )
