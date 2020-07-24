/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "CsvFileWriterTestCommon.h"

TEST_CASE("filePath")
{
  CsvFileWriter writer;

  SECTION("default")
  {
    REQUIRE( writer.filePath().empty() );
  }

  SECTION("set and get")
  {
    writer.setFilePath("test.csv");
    REQUIRE( writer.filePath() == "test.csv" );
  }
}

TEST_CASE("csvSettings")
{
  CsvFileWriter writer;

  SECTION("default")
  {
    REQUIRE(false);
  }

  SECTION("set and get")
  {
    REQUIRE(false);
  }
}

TEST_CASE("openMode")
{
  CsvFileWriter writer;

  SECTION("default")
  {
    REQUIRE( writer.openMode() == FileWriteOpenMode::Append );
  }

  SECTION("set and get")
  {
    writer.setOpenMode(FileWriteOpenMode::Truncate);
    REQUIRE( writer.openMode() == FileWriteOpenMode::Truncate );
  }
}
