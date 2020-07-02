##############################################################
#  Copyright Philippe Steinmann 2020 - 2020.
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt)
##############################################################
include(MdtAddTest)

mdt_add_test(
  NAME BoostSpiritQStringContainerTest
  TARGET boostSpiritQStringContainerTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::Catch2Main
  SOURCE_FILES
    src/BoostSpiritQStringContainerTest.cpp
)

mdt_add_test(
  NAME BoostSpiritQStringConstIteratorTest
  TARGET boostSpiritQStringConstIteratorTest
  DEPENDENCIES Mdt::PlainText_QtCore Mdt::Catch2Main
  SOURCE_FILES
    src/BoostSpiritQStringConstIteratorTest.cpp
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
