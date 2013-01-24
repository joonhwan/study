get_filename_component(DEFAULT_QT_ZLIB_DIR "${QT_QTGUI_INCLUDE_DIR}/../../src/3rdparty/zlib"  ABSOLUTE)
set(QT_ZLIB_DIR ${DEFAULT_QT_ZLIB_DIR} CACHE PATH "Qt의 3rdparty/zlib 디렉토리 위치")
if(NOT QT_ZLIB_DIR)
  message(SEND_ERROR "QT_ZLIB_DIR가 설정되어 있지 않습니다.")
endif()
include_directories(${QT_ZLIB_DIR})

