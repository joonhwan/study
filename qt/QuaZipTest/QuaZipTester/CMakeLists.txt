set(CURR_PRJ QuaZipTester)

set(QT_USE_QTMAIN ON)
include(${QT_USE_FILE})

add_definitions(
  -DQUAZIP_STATIC
  )
include_directories(
  ${QT_ZLIB_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/..
  )

set(sources
  main.cpp
  WTempDir.cpp
  WZipFileDelegate.cpp
  )

set(moc_header
  )

set(header
  WTempDir.h
  WZipFileDelegate.h
  )

set(forms
  )

set(resources
  )

qt4_wrap_cpp(moc_generated ${moc_header})
qt4_wrap_ui(forms_generated ${forms})
qt4_add_resources(rc_generated ${resources})

add_executable(${CURR_PRJ} WIN32 MACOSX_BUNDLE
  ${sources}
  ${header}
  ${moc_header}
  ${form}
  ${resource}
  ${moc_generated}
  ${forms_generated}
  ${rc_generated}
  )

target_link_libraries(${CURR_PRJ}
  ${QT_LIBRARIES}
  QuaZip
  )
