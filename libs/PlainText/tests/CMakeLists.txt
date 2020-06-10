##############################################################
#  Copyright Philippe Steinmann 2020 - 2020.
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt)
##############################################################
include(MdtAddTest)

mdt_add_test(
  NAME CsvFileReaderTest
  TARGET csvFileReaderTest
  DEPENDENCIES Mdt::PlainText Mdt::Catch2Main
  SOURCE_FILES
    src/CsvFileReaderTest.cpp
)

mdt_add_test(
  NAME CsvFileReaderErrorTest
  TARGET csvFileReaderErrorTest
  DEPENDENCIES Mdt::PlainText Mdt::Catch2Main
  SOURCE_FILES
    src/CsvFileReaderErrorTest.cpp
)