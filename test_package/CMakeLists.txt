##############################################################
#  Copyright Philippe Steinmann 2020 - 2020.
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt)
##############################################################
cmake_minimum_required(VERSION 3.10)

project(MdtPlainTextTest)

if(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
  include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
  conan_basic_setup(NO_OUTPUT_DIRS)
endif()

find_package(Threads REQUIRED)
find_package(MdtCMakeModules REQUIRED)
find_package(Boost REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Mdt0 COMPONENTS PlainText_QtCore REQUIRED)

include(MdtAddTest)

enable_testing()


mdt_add_test(
  NAME ReadCsvFile
  TARGET readCsvFile
  DEPENDENCIES Mdt0::PlainText_QtCore
  SOURCE_FILES
    ReadCsvFile.cpp
)
target_compile_definitions(readCsvFile PRIVATE TEST_FILE="${PROJECT_SOURCE_DIR}/file.csv")
