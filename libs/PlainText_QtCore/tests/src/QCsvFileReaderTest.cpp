/****************************************************************************
 **
 ** MdtPlainText - A C++ library to read and write simple plain text
 ** using the boost Spirit library.
 **
 ** Copyright (C) 2020-2020 Philippe Steinmann.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with this program.  If not, see <https://www.gnu.org/licenses/>.
 **
 ****************************************************************************/
#include "QCsvFileReaderTestCommon.h"

TEST_CASE("filePath")
{
  QCsvFileReader reader;
  REQUIRE( reader.filePath().isEmpty() );
  reader.setFilePath(QLatin1String("tests.csv"));
  REQUIRE( reader.filePath() == QLatin1String("tests.csv") );
}

TEST_CASE("fileEncoding")
{
  QCsvFileReader reader;
  REQUIRE( reader.fileEncoding() == "UTF-8" );

  reader.setFileEncoding("ISO 8859-1");
  REQUIRE( reader.fileEncoding() == "ISO 8859-1" );
}

TEST_CASE("csvSettings")
{
  QCsvFileReader reader;
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

  QCsvFileReader reader;
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

  QCsvFileReader reader;
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

  QCsvFileReader reader;
  setFilePathToReader(file, reader);

  SECTION("1 line")
  {
    REQUIRE( writeTextFile(file, QLatin1String("A,B,C")) );
    file.close();

    reader.open();
    REQUIRE( !reader.atEnd() );
    REQUIRE( recordMatches( reader.readLine(), {"A","B","C"} ) );
    REQUIRE( reader.atEnd() );
  }

  SECTION("2 lines")
  {
    REQUIRE( writeTextFile(file, QLatin1String("A,B,C\nd,e,f")) );
    file.close();

    reader.open();
    REQUIRE( !reader.atEnd() );

    REQUIRE( recordMatches( reader.readLine(), {"A","B","C"} ) );
    REQUIRE( !reader.atEnd() );

    REQUIRE( recordMatches( reader.readLine(), {"d","e","f"} ) );
    REQUIRE( reader.atEnd() );
  }
}

TEST_CASE("readAll")
{
  QTemporaryFile file;
  REQUIRE( file.open() );

  std::vector< std::vector<std::string> > referenceTable;

  QCsvFileReader reader;
  setFilePathToReader(file, reader);

  SECTION("1 line")
  {
    REQUIRE( writeTextFile(file, QLatin1String("A,B,C")) );
    file.close();

    reader.open();
    REQUIRE( !reader.atEnd() );

    referenceTable = {
      {"A","B","C"}
    };
    REQUIRE( tableMatches(reader.readAll(), referenceTable) );
    REQUIRE( reader.atEnd() );
  }

  SECTION("2 lines")
  {
    REQUIRE( writeTextFile(file, QLatin1String("A,B,C\nd,e,f")) );
    file.close();

    reader.open();
    REQUIRE( !reader.atEnd() );

    referenceTable = {
      {"A","B","C"},
      {"d","e","f"}
    };
    REQUIRE( tableMatches(reader.readAll(), referenceTable) );
    REQUIRE( reader.atEnd() );
  }
}

TEST_CASE("Test files")
{
  CsvParserSettings csvSettings;
  QCsvFileReader reader;

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
