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

TEST_CASE("readLine")
{
  QTemporaryFile file;
  REQUIRE( file.open() );

  std::vector<std::string> record;

  CsvFileReader reader;
  setFilePathToReader(file, reader);

  SECTION("1 line")
  {
    REQUIRE( writeTextFile(file, QLatin1String("A,B,C")) );
    file.close();

    reader.open();
    REQUIRE( !reader.atEnd() );

    record = reader.readLine();
    REQUIRE( record.size() == 3 );
    REQUIRE( record[0] == "A" );
    REQUIRE( record[1] == "B" );
    REQUIRE( record[2] == "C" );
    REQUIRE( reader.atEnd() );
  }

  SECTION("2 lines")
  {
    REQUIRE( writeTextFile(file, QLatin1String("A,B,C\nd,e,f")) );
    file.close();

    reader.open();
    REQUIRE( !reader.atEnd() );

    record = reader.readLine();
    REQUIRE( record.size() == 3 );
    REQUIRE( record[0] == "A" );
    REQUIRE( record[1] == "B" );
    REQUIRE( record[2] == "C" );
    REQUIRE( !reader.atEnd() );

    record = reader.readLine();
    REQUIRE( record.size() == 3 );
    REQUIRE( record[0] == "d" );
    REQUIRE( record[1] == "e" );
    REQUIRE( record[2] == "f" );
    REQUIRE( reader.atEnd() );
  }
}

TEST_CASE("readAll")
{
  QTemporaryFile file;
  REQUIRE( file.open() );

  std::vector< std::vector<std::string> > table;

  CsvFileReader reader;
  setFilePathToReader(file, reader);

  SECTION("1 line")
  {
    REQUIRE( writeTextFile(file, QLatin1String("A,B,C")) );
    file.close();

    reader.open();
    REQUIRE( !reader.atEnd() );

    table = reader.readAll();
    REQUIRE( table.size() == 1 );
    REQUIRE( table[0][0] == "A" );
    REQUIRE( table[0][1] == "B" );
    REQUIRE( table[0][2] == "C" );
    REQUIRE( reader.atEnd() );
  }

  SECTION("2 lines")
  {
    REQUIRE( writeTextFile(file, QLatin1String("A,B,C\nd,e,f")) );
    file.close();

    reader.open();
    REQUIRE( !reader.atEnd() );

    table = reader.readAll();
    REQUIRE( table.size() == 2 );
    REQUIRE( table[0][0] == "A" );
    REQUIRE( table[0][1] == "B" );
    REQUIRE( table[0][2] == "C" );
    REQUIRE( table[1][0] == "d" );
    REQUIRE( table[1][1] == "e" );
    REQUIRE( table[1][2] == "f" );
    REQUIRE( reader.atEnd() );
  }
}

TEST_CASE("Test files")
{
  std::vector< std::vector<std::string> > table;
  CsvParserSettings csvSettings;
  CsvFileReader reader;

  SECTION("Wikipedia_car_example_UTF8")
  {
    setTestFilePathToReader("Wikipedia_car_example_UTF8.csv", reader);

    reader.open();
    REQUIRE( !reader.atEnd() );
    REQUIRE( tableMatches( reader.readAll(), Wikipedia_car_example_ReferenceTable() ) );
  }

  SECTION("Wikipedia_European_UK_example_UTF8")
  {
    setTestFilePathToReader("Wikipedia_European_UK_example_UTF8.csv", reader);

    reader.open();
    REQUIRE( !reader.atEnd() );
    REQUIRE( tableMatches( reader.readAll(), Wikipedia_European_UK_example_ReferenceTable() ) );
  }

  SECTION("Wikipedia_USA_UK_example_UTF8")
  {
    csvSettings.setFieldSeparator(';');
    reader.setCsvSettings(csvSettings);

    setTestFilePathToReader("Wikipedia_USA_UK_example_UTF8.csv", reader);

    reader.open();
    REQUIRE( !reader.atEnd() );
    REQUIRE( tableMatches( reader.readAll(), Wikipedia_USA_UK_example_ReferenceTable() ) );
  }
}
