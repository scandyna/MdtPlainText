##############################################################
#  Copyright Philippe Steinmann 2020 - 2020.
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt)
##############################################################
include(MdtAddTest)

mdt_add_test(
  NAME CsvParserSettingsTest
  TARGET csvParserSettingsTest
  DEPENDENCIES Mdt::PlainText Mdt::Catch2Main
  SOURCE_FILES
    src/CsvParserSettingsTest.cpp
)

mdt_add_test(
  NAME CsvFileReaderTest
  TARGET csvFileReaderTest
  DEPENDENCIES Mdt::PlainText Mdt::Catch2Main Qt5::Test
  SOURCE_FILES
    src/CsvFileReaderTest.cpp
)
target_compile_definitions(csvFileReaderTest PRIVATE TEST_FILES_DIR="${PROJECT_SOURCE_DIR}/libs/PlainText/tests/files")

mdt_add_test(
  NAME CsvFileReaderErrorTest
  TARGET csvFileReaderErrorTest
  DEPENDENCIES Mdt::PlainText Mdt::Catch2Main Qt5::Test
  SOURCE_FILES
    src/CsvFileReaderErrorTest.cpp
)
target_compile_definitions(csvFileReaderErrorTest PRIVATE TEST_FILES_DIR="${PROJECT_SOURCE_DIR}/libs/PlainText/tests/files")
