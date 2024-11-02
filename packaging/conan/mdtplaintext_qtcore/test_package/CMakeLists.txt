##############################################################
#  Copyright Philippe Steinmann 2020 - 2024.
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt)
##############################################################
cmake_minimum_required(VERSION 3.15)

project(MdtPlainTextTest)


find_package(MdtCMakeModules REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(Mdt0 REQUIRED COMPONENTS PlainText_QtCore)

include(MdtAddTest)

enable_testing()


mdt_add_test(
  NAME ReadCsvFileQt
  TARGET readCsvFileQt
  DEPENDENCIES Mdt0::PlainText_QtCore
  SOURCE_FILES
    ReadCsvFileQt.cpp
)
target_compile_definitions(readCsvFileQt PRIVATE TEST_FILE="${PROJECT_SOURCE_DIR}/file.csv")
