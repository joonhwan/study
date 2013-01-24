set(QT_USE_QTMAIN ON)
include(${QT_USE_FILE})

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  )


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

add_executable(ReadEvalPrintLoopWidget WIN32 MACOSX_BUNDLE
  ${sources}
  ${header}
  ${moc_header}
  ${form}
  ${resource}
  ${moc_generated}
  ${forms_generated}
  ${rc_generated}
  )

target_link_libraries(ReadEvalPrintLoopWidget
  ${QT_LIBRARIES}
  )

