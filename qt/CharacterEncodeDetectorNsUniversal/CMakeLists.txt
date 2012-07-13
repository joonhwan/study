
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(EncodeDetector)

# Set up the environment
find_package(Qt4 REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# SET(QT_USE_QTMAIN ON)
include(${QT_USE_FILE})

set(sources
  CharDistribution.cpp JpCntx.cpp LangBulgarianModel.cpp LangCyrillicModel.cpp LangGreekModel.cpp LangHebrewModel.cpp LangHungarianModel.cpp LangThaiModel.cpp nsBig5Prober.cpp nsCharSetProber.cpp nsEscCharsetProber.cpp nsEscSM.cpp nsEUCJPProber.cpp nsEUCKRProber.cpp nsEUCTWProber.cpp nsGB2312Prober.cpp nsHebrewProber.cpp nsLatin1Prober.cpp nsMBCSGroupProber.cpp nsMBCSSM.cpp nsSBCharSetProber.cpp nsSBCSGroupProber.cpp nsSJISProber.cpp nsUniversalDetector.cpp nsUTF8Prober.cpp
  main.cpp
  )

set(moc_header
  )

set(header
  CharDistribution.h JpCntx.h nsBig5Prober.h nsCharSetProber.h nsCodingStateMachine.h nscore.h nsEscCharsetProber.h nsEUCJPProber.h nsEUCKRProber.h nsEUCTWProber.h nsGB2312Prober.h nsHebrewProber.h nsLatin1Prober.h nsMBCSGroupProber.h nsPkgInt.h nsSBCharSetProber.h nsSBCSGroupProber.h nsSJISProber.h nsUniversalDetector.h nsUTF8Prober.h prmem.h
  )

set(forms
  )

set(resources
  )

qt4_wrap_cpp(moc_generated ${moc_header})
qt4_wrap_ui(forms_generated ${forms})
qt4_add_resources(rc_generated ${resources})

add_executable(${PROJECT_NAME}
  # WIN32
  MACOSX_BUNDLE
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
  )
