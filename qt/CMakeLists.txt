cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(QtStudy)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up the environment
find_package(Qt4 REQUIRED)

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  )

add_subdirectory(UsingCustomTypeInSignalSlot)
add_subdirectory(ReadEvalPrintLoopWidget)
add_subdirectory(QuaZipTest)
add_subdirectory(ScriptTest)
