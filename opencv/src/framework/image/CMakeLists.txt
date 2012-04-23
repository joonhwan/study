PROJECT(image)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

INCLUDE(${QT_USE_FILE})

SET(sources
  WHistogram.cpp
  WImageBuffer.cpp
  WImageBufferT.cpp
  WImageProcessor.cpp
  )

SET(moc_header
  )

SET(header
  ippi.hpp
  ippi_ext.hpp
  Vld.h
  WConstImageT.h
  WHistogram.h
  WImageBuffer.h
  WImageBuffer.inl
  WImageBufferT.h
  WImageBufferT.inl
  WImageBufferTraits.h
  WImageProcessor.h
  WImageProcessorMacros.h
  WImageT.h
  WImageUtils.h
  WIppKernel.h
  WLookupTable.h
  WLookupTableTraits.h
  WPixel.h
  WStopwatch.h
  ippi.hpp
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
  ${IPP_LIBRARIES}
  ${VLD_LIBRARIES}
  ${OPENCV_LIBRARIES}
  )

