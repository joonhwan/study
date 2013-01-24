include(QuaZipConfig.cmake)

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${QT_ZLIB_DIR}
  )

include(${QT_USE_FILE})

set(QuaZip_sources
  JlCompress.cpp
  qioapi.cpp
  quaadler32.cpp
  quacrc32.cpp
  quagzipfile.cpp
  quaziodevice.cpp
  quazip.cpp
  quazipdir.cpp
  quazipfile.cpp
  quazipnewinfo.cpp
  unzip.c
  zip.c
  )

set(QuaZip_moc_headers
  quagzipfile.h
  quaziodevice.h
  quazipfile.h
  )

set(QuaZip_headers
  crypt.h
  ioapi.h
  JlCompress.h
  quaadler32.h
  quachecksum32.h
  quacrc32.h
  quagzipfile.h
  quaziodevice.h
  quazip.h
  quazipdir.h
  quazipfile.h
  quazipfileinfo.h
  quazipnewinfo.h
  quazip_global.h
  unzip.h
  zip.h
  )

add_definitions(
  # -DQUAZIP_BUILD
  -DQUAZIP_STATIC
  )
