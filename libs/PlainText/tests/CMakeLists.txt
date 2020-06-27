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
  NAME CsvGrammarTest
  TARGET csvGrammarTest
  DEPENDENCIES Mdt::PlainText Mdt::Catch2Main
  SOURCE_FILES
    src/CsvGrammarTest.cpp
)

mdt_add_test(
  NAME CsvGrammarErrorTest
  TARGET csvGrammarErrorTest
  DEPENDENCIES Mdt::PlainText Mdt::Catch2Main
  SOURCE_FILES
    src/CsvGrammarErrorTest.cpp
)

mdt_add_test(
  NAME CsvParserTemplateTest
  TARGET csvParserTemplateTest
  DEPENDENCIES Mdt::PlainText Mdt::Catch2Main
  SOURCE_FILES
    src/CsvParserTemplateTest.cpp
)

mdt_add_test(
  NAME CsvParserTemplateErrorTest
  TARGET csvParserTemplateErrorTest
  DEPENDENCIES Mdt::PlainText Mdt::Catch2Main
  SOURCE_FILES
    src/CsvParserTemplateErrorTest.cpp
)

mdt_add_test(
  NAME CsvFileReaderTest
  TARGET csvFileReaderTest
  DEPENDENCIES Mdt::PlainText Mdt::Catch2Main Qt5::Test Mdt::PlainText_TestLib
  SOURCE_FILES
    src/CsvFileReaderTest.cpp
)

mdt_add_test(
  NAME CsvFileReaderErrorTest
  TARGET csvFileReaderErrorTest
  DEPENDENCIES Mdt::PlainText Mdt::Catch2Main Qt5::Test Mdt::PlainText_TestLib
  SOURCE_FILES
    src/CsvFileReaderErrorTest.cpp
)
