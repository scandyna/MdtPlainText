/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "CsvFileReaderTestCommon.h"

TEST_CASE("open")
{
  CsvFileReader reader;

  SECTION("File not exists")
  {
    reader.setFilePath("/some/non/exising/file.csv");

    REQUIRE_THROWS_AS( reader.open(), FileOpenError );
  }

  /*
   * See https://stackoverflow.com/questions/9591036/ifstream-open-doesnt-set-error-bits-when-argument-is-a-directory
   */
  SECTION("Path refers to a directory")
  {
    QTemporaryDir dir;
    REQUIRE( dir.isValid() );

    setDirectoryPathToReader(dir, reader);

    REQUIRE_THROWS_AS( reader.open(), FileOpenError );
  }
}
