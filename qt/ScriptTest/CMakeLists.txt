# Set up the environment
find_package(Qt4 REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# SET(QT_USE_QTMAIN ON)
SET(QT_USE_QTSCRIPT ON)
include(${QT_USE_FILE})

set(sources
  main.cpp
  Defect.cpp
  )

set(moc_header
  Defect.h
  )

set(header
  )

set(forms
  )

set(resources
  )

qt4_wrap_cpp(moc_generated ${moc_header})
qt4_wrap_ui(forms_generated ${forms})
qt4_add_resources(rc_generated ${resources})

add_executable(ScriptTest
  # MACOSX_BUNDLE
  ${sources}
  ${header}
  ${moc_header}
  ${form}
  ${resource}
  ${moc_generated}
  ${forms_generated}
  ${rc_generated}
  )

target_link_libraries(ScriptTest
  ${QT_LIBRARIES}
  )
