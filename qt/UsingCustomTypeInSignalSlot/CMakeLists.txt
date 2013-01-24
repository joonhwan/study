# Set up the environment
find_package(Qt4 REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# SET(QT_USE_QTMAIN ON)
include(${QT_USE_FILE})

set(sources
  main.cpp
  MainWindow.cpp
  )

set(moc_header
  MainWindow.h
  )

set(header
  TestClass.h
  )

set(forms
  )

set(resources
  )

qt4_wrap_cpp(moc_generated ${moc_header})
qt4_wrap_ui(forms_generated ${forms})
qt4_add_resources(rc_generated ${resources})

add_executable(UsingCustomTypeInSignalSlot MACOSX_BUNDLE
  ${sources}
  ${header}
  ${moc_header}
  ${form}
  ${resource}
  ${moc_generated}
  ${forms_generated}
  ${rc_generated}
  )

target_link_libraries(UsingCustomTypeInSignalSlot
  ${QT_LIBRARIES}
  )
