/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "CsvFileWriterTestCommon.h"

TEST_CASE("open")
{
  CsvFileWriter writer;

  SECTION("Path refers to a directory")
  {
    QTemporaryDir dir;
    REQUIRE( dir.isValid() );

    setDirectoryPathToWriter(dir, writer);

    REQUIRE_THROWS_AS( writer.open(), FileOpenError );
    REQUIRE( !writer.isOpen() );
  }
}
