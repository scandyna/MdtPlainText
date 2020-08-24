##############################################################
#  Copyright Philippe Steinmann 2020 - 2020.
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt)
##############################################################
include(MdtAddTest)

mdt_add_test(
  NAME AddCodePointToQStringTest
  TARGET addCodePointToQStringTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::Catch2Main
  SOURCE_FILES
    src/AddCodePointToQStringTest.cpp
)

mdt_add_test(
  NAME QStringUnicodeViewTest
  TARGET qStringUnicodeViewTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::Catch2Main
  SOURCE_FILES
    src/QStringUnicodeViewTest.cpp
)

mdt_add_test(
  NAME QStringUnicodeViewBoostSpiritKarmaTest
  TARGET qStringUnicodeViewBoostSpiritKarmaTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::Catch2Main
  SOURCE_FILES
    src/QStringUnicodeViewBoostSpiritKarmaTest.cpp
)

mdt_add_test(
  NAME QStringContainerUnicodeConstIteratorTest
  TARGET qStringContainerUnicodeConstIteratorTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::Catch2Main
  SOURCE_FILES
    src/QStringContainerUnicodeConstIteratorTest.cpp
)

mdt_add_test(
  NAME QStringListUnicodeViewTest
  TARGET qStringListUnicodeViewTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::Catch2Main
  SOURCE_FILES
    src/QStringListUnicodeViewTest.cpp
)

mdt_add_test(
  NAME QStringListUnicodeViewBoostSpiritKarmaTest
  TARGET qStringListUnicodeViewBoostSpiritKarmaTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::Catch2Main
  SOURCE_FILES
    src/QStringListUnicodeViewBoostSpiritKarmaTest.cpp
)

mdt_add_test(
  NAME QStringUnicodeConstIteratorTest
  TARGET qStringUnicodeConstIteratorTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::Catch2Main
  SOURCE_FILES
    src/QStringUnicodeConstIteratorTest.cpp
)

mdt_add_test(
  NAME QStringUnicodeConstIteratorBoostSpiritTest
  TARGET qStringUnicodeConstIteratorBoostSpiritTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::Catch2Main
  SOURCE_FILES
    src/QStringUnicodeConstIteratorBoostSpiritTest.cpp
)

mdt_add_test(
  NAME QStringUnicodeBackInsertIteratorTest
  TARGET qStringUnicodeBackInsertIteratorTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::Catch2Main
  SOURCE_FILES
    src/QStringUnicodeBackInsertIteratorTest.cpp
)

mdt_add_test(
  NAME QStringIteratorStlTest
  TARGET qStringIteratorStlTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::Catch2Main
  SOURCE_FILES
    src/QStringIteratorStlTest.cpp
)

mdt_add_test(
  NAME QTextFileInputConstIteratorSharedDataTest
  TARGET qTextFileInputConstIteratorSharedDataTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::PlainText_TestLib Mdt::Catch2Main
  SOURCE_FILES
    src/QTextFileInputConstIteratorSharedDataTest.cpp
)

mdt_add_test(
  NAME QTextFileInputConstIteratorSharedDataErrorTest
  TARGET qTextFileInputConstIteratorSharedDataErrorTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::PlainText_TestLib Mdt::Catch2Main
  SOURCE_FILES
    src/QTextFileInputConstIteratorSharedDataErrorTest.cpp
)

mdt_add_test(
  NAME QTextFileInputConstIteratorTest
  TARGET qTextFileInputConstIteratorTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::PlainText_TestLib Mdt::Catch2Main
  SOURCE_FILES
    src/QTextFileInputConstIteratorTest.cpp
)

mdt_add_test(
  NAME QTextFileInputConstIteratorErrorTest
  TARGET qTextFileInputConstIteratorErrorTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::PlainText_TestLib Mdt::Catch2Main
  SOURCE_FILES
    src/QTextFileInputConstIteratorErrorTest.cpp
)

mdt_add_test(
  NAME BoostSpiritQTextFileInputConstIteratorTest
  TARGET boostSpiritQTextFileInputConstIteratorTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::PlainText_TestLib Mdt::Catch2Main
  SOURCE_FILES
    src/BoostSpiritQTextFileInputConstIteratorTest.cpp
)

mdt_add_test(
  NAME BoostSpiritQTextFileInputConstIteratorErrorTest
  TARGET boostSpiritQTextFileInputConstIteratorErrorTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::PlainText_TestLib Mdt::Catch2Main
  SOURCE_FILES
    src/BoostSpiritQTextFileInputConstIteratorErrorTest.cpp
)

mdt_add_test(
  NAME QCsvGrammarTest
  TARGET qCsvGrammarTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::Catch2Main Mdt::PlainText_TestLib
  SOURCE_FILES
    src/QCsvGrammarTest.cpp
)

mdt_add_test(
  NAME QCsvGrammarErrorTest
  TARGET qCsvGrammarErrorTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::Catch2Main Mdt::PlainText_TestLib
  SOURCE_FILES
    src/QCsvGrammarErrorTest.cpp
)

mdt_add_test(
  NAME QCsvFileReaderTest
  TARGET qCsvFileReaderTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::Catch2Main Mdt::PlainText_TestLib
  SOURCE_FILES
    src/QCsvFileReaderTest.cpp
)

mdt_add_test(
  NAME QCsvFileReaderErrorTest
  TARGET qCsvFileReaderErrorTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::Catch2Main Mdt::PlainText_TestLib
  SOURCE_FILES
    src/QCsvFileReaderErrorTest.cpp
)

mdt_add_test(
  NAME QCsvKarmaGrammarTest
  TARGET qCsvKarmaGrammarTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::Catch2Main Mdt::PlainText_TestLib
  SOURCE_FILES
    src/QCsvKarmaGrammarTest.cpp
)

mdt_add_test(
  NAME QCsvKarmaGrammarErrorTest
  TARGET qCsvKarmaGrammarErrorTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::Catch2Main Mdt::PlainText_TestLib
  SOURCE_FILES
    src/QCsvKarmaGrammarErrorTest.cpp
)

mdt_add_test(
  NAME QCsvFileWriterTest
  TARGET qCsvFileWriterTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::Catch2Main Mdt::PlainText_TestLib
  SOURCE_FILES
    src/QCsvFileWriterTest.cpp
)

mdt_add_test(
  NAME QCsvFileWriterErrorTest
  TARGET qCsvFileWriterErrorTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::Catch2Main Mdt::PlainText_TestLib
  SOURCE_FILES
    src/QCsvFileWriterErrorTest.cpp
)
