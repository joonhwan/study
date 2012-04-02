PROJECT(common)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

INCLUDE(${QT_USE_FILE})

SET(sources
  wimage.cpp
  wimageipp.cpp
  wimage_t.cpp
  )

SET(moc_header
  )

SET(header
  common.h
  vldhelper.h
  wimage.h
  wimage.inl
  wimageipp.h
  wimage_convert.h
  wimage_p.h
  wimage_t.h
  wimage_t_traits.h
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
