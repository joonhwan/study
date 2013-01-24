set(CURR_PRJ "QuaZip")

include(QuaZip.cmake)

add_definitions(
  # -DQUAZIP_BUILD
  -DQUAZIP_STATIC
  )

set(sources
  ${QuaZip_sources}
  )

set(moc_header
  ${QuaZip_moc_headers}
  )

set(header
  ${QuaZip_headers}
  )

set(forms
  )

set(resources
  )

qt4_wrap_cpp(moc_generated ${moc_header})
qt4_wrap_ui(forms_generated ${forms})
qt4_add_resources(rc_generated ${resources})

add_library(${CURR_PRJ}
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
  )
