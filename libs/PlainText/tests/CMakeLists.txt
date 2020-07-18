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
  DEPENDENCIES Mdt::PlainText Boost::boost Mdt::Catch2Main
  SOURCE_FILES
    src/CsvGrammarTest.cpp
)

mdt_add_test(
  NAME CsvGrammarErrorTest
  TARGET csvGrammarErrorTest
  DEPENDENCIES Mdt::PlainText Boost::boost Mdt::Catch2Main
  SOURCE_FILES
    src/CsvGrammarErrorTest.cpp
)

if(UNIX)
  mdt_add_test(
    NAME BasicFileInfo_unix_Test
    TARGET basicFileInfo_unix_Test
    DEPENDENCIES Mdt::PlainText Mdt::Catch2Main Qt5::Core
    SOURCE_FILES
      src/BasicFileInfo_unix_Test.cpp
  )
endif()

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
