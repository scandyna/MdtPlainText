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

    table = reader.readAll();
    REQUIRE( table.size() == 5 );
    REQUIRE( table[0][0] == "Year" );
    REQUIRE( table[0][1] == "Make" );
    REQUIRE( table[0][2] == "Model" );
    REQUIRE( table[0][3] == "Description" );
    REQUIRE( table[0][4] == "Price" );
    REQUIRE( table[1][0] == "1997" );
    REQUIRE( table[1][1] == "Ford" );
    REQUIRE( table[1][2] == "E350" );
    REQUIRE( table[1][3] == "ac, abs, moon" );
    REQUIRE( table[1][4] == "3000.00" );
    REQUIRE( table[2][0] == "1999" );
    REQUIRE( table[2][1] == "Chevy" );
    REQUIRE( table[2][2] == "Venture \"Extended Edition\"" );
    REQUIRE( table[2][3] == "" );
    REQUIRE( table[2][4] == "4900.00" );
    REQUIRE( table[3][0] == "1999" );
    REQUIRE( table[3][1] == "Chevy" );
    REQUIRE( table[3][2] == "Venture \"Extended Edition, Very Large\"" );
    REQUIRE( table[3][3] == "" );
    REQUIRE( table[3][4] == "5000.00" );
    REQUIRE( table[4][0] == "1996" );
    REQUIRE( table[4][1] == "Jeep" );
    REQUIRE( table[4][2] == "Grand Cherokee" );
    REQUIRE( table[4][3] == "MUST SELL!\nair, moon roof, loaded" );
    REQUIRE( table[4][4] == "4799.00" );
  }

  SECTION("Wikipedia_European_UK_example_UTF8")
  {
    setTestFilePathToReader("Wikipedia_European_UK_example_UTF8.csv", reader);

    reader.open();
    REQUIRE( !reader.atEnd() );

    table = reader.readAll();
    REQUIRE( table.size() == 3 );
    REQUIRE( table[0][0] == "Year" );
    REQUIRE( table[0][1] == "Make" );
    REQUIRE( table[0][2] == "Model" );
    REQUIRE( table[0][3] == "Length" );
    REQUIRE( table[1][0] == "1997" );
    REQUIRE( table[1][1] == "Ford" );
    REQUIRE( table[1][2] == "E350" );
    REQUIRE( table[1][3] == "2.35" );
    REQUIRE( table[2][0] == "2000" );
    REQUIRE( table[2][1] == "Mercury" );
    REQUIRE( table[2][2] == "Cougar" );
    REQUIRE( table[2][3] == "2.38" );
  }

  SECTION("Wikipedia_USA_UK_example_UTF8")
  {
    csvSettings.setFieldSeparator(';');
    reader.setCsvSettings(csvSettings);

    setTestFilePathToReader("Wikipedia_USA_UK_example_UTF8.csv", reader);

    reader.open();
    REQUIRE( !reader.atEnd() );

    table = reader.readAll();
    REQUIRE( table.size() == 3 );
    REQUIRE( table[0][0] == "Year" );
    REQUIRE( table[0][1] == "Make" );
    REQUIRE( table[0][2] == "Model" );
    REQUIRE( table[0][3] == "Length" );
    REQUIRE( table[1][0] == "1997" );
    REQUIRE( table[1][1] == "Ford" );
    REQUIRE( table[1][2] == "E350" );
    REQUIRE( table[1][3] == "2,35" );
    REQUIRE( table[2][0] == "2000" );
    REQUIRE( table[2][1] == "Mercury" );
    REQUIRE( table[2][2] == "Cougar" );
    REQUIRE( table[2][3] == "2,38" );
  }
}
