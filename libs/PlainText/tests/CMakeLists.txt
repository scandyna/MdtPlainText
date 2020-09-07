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
  NAME CsvQiGrammarTest
  TARGET csvQiGrammarTest
  DEPENDENCIES Mdt::PlainText Boost::boost Mdt::Catch2Main
  SOURCE_FILES
    src/CsvQiGrammarTest.cpp
)

mdt_add_test(
  NAME CsvQiGrammarErrorTest
  TARGET csvQiGrammarErrorTest
  DEPENDENCIES Mdt::PlainText Boost::boost Mdt::Catch2Main
  SOURCE_FILES
    src/CsvQiGrammarErrorTest.cpp
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
  NAME CsvGeneratorSettingsTest
  TARGET csvGeneratorSettingsTest
  DEPENDENCIES Mdt::PlainText Mdt::Catch2Main Qt5::Test Mdt::PlainText_TestLib
  SOURCE_FILES
    src/CsvGeneratorSettingsTest.cpp
)

mdt_add_test(
  NAME CsvKarmaGrammarTest
  TARGET csvKarmaGrammarTest
  DEPENDENCIES Mdt::PlainText Boost::boost Mdt::Catch2Main
  SOURCE_FILES
    src/CsvKarmaGrammarTest.cpp
)

mdt_add_test(
  NAME CsvKarmaGrammarErrorTest
  TARGET csvKarmaGrammarErrorTest
  DEPENDENCIES Mdt::PlainText Boost::boost Mdt::Catch2Main
  SOURCE_FILES
    src/CsvKarmaGrammarErrorTest.cpp
)

mdt_add_test(
  NAME CsvFileWriterTest
  TARGET csvFileWriterTest
  DEPENDENCIES Mdt::PlainText Mdt::Catch2Main Qt5::Test Mdt::PlainText_TestLib
  SOURCE_FILES
    src/CsvFileWriterTest.cpp
)

mdt_add_test(
  NAME CsvFileWriterErrorTest
  TARGET csvFileWriterErrorTest
  DEPENDENCIES Mdt::PlainText Mdt::Catch2Main Qt5::Test Mdt::PlainText_TestLib
  SOURCE_FILES
    src/CsvFileWriterErrorTest.cpp
)

mdt_add_test(
  NAME ContainerAliasViewConstIteratorTest
  TARGET containerAliasViewConstIteratorTest
  DEPENDENCIES Mdt::PlainText Mdt::Catch2Main Mdt::PlainText_TestLib
  SOURCE_FILES
    src/ContainerAliasViewConstIteratorTest.cpp
)

mdt_add_test(
  NAME ContainerAliasViewTest
  TARGET containerAliasViewTest
  DEPENDENCIES Mdt::PlainText Mdt::Catch2Main Mdt::PlainText_TestLib
  SOURCE_FILES
    src/ContainerAliasViewTest.cpp
)
