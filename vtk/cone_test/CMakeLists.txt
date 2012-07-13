project(cone_test)

# Set up the environment
find_package(Qt4 REQUIRED)

include(${VTK_USE_FILE})

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  )

set(QT_USE_QTMAIN ON)
include(${QT_USE_FILE})

set(sources
  GUI4.cpp main.cpp
  )

set(moc_header
  GUI4.h
  )

set(header
  )

set(forms
  GUI4.ui
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
  ${VTK_LIBRARIES}
  QVTK
  )
