cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(eignetest)

# Set up the environment
find_package(Qt4 REQUIRED)

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  c:/dev/sdk/eigen
  )

set(QT_USE_QTMAIN ON)
include(${QT_USE_FILE})

add_subdirectory(helloEigen)
