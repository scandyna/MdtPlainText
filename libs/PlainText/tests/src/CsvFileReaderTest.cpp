/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "CsvFileReaderTestCommon.h"

TEST_CASE("filePath")
{
  CsvFileReader reader;
  REQUIRE( reader.filePath().empty() );
  reader.setFilePath("tests.csv");
  REQUIRE( reader.filePath() == "tests.csv" );
}

TEST_CASE("csvSettings")
{
  CsvFileReader reader;
  CsvParserSettings settings;

  settings.setFieldSeparator(';');
  reader.setCsvSettings(settings);
  REQUIRE( reader.csvSettings().fieldSeparator() == ';' );
}

TEST_CASE("open_close")
{
  QTemporaryFile file;
  REQUIRE( file.open() );
  REQUIRE( writeSimpleCsvFile(file) );
  file.close();

  CsvFileReader reader;
  REQUIRE( !reader.isOpen() );

  setFilePathToReader(file, reader);
  REQUIRE( !reader.isOpen() );

  reader.open();
  REQUIRE( reader.isOpen() );

  reader.close();
  REQUIRE( !reader.isOpen() );
}

TEST_CASE("atEnd")
{
  QTemporaryFile file;
  REQUIRE( file.open() );

  CsvFileReader reader;
  setFilePathToReader(file, reader);

  SECTION("empty")
  {
    file.close();

    reader.open();
    REQUIRE( reader.atEnd() );
  }

  SECTION("1 line")
  {
    REQUIRE( writeTextFile(file, QLatin1String("A,B,C")) );
    file.close();

    reader.open();
    REQUIRE( !reader.atEnd() );
  }
}
