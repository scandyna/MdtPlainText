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
#include "QCsvFileWriterTestCommon.h"

TEST_CASE("filePath")
{
  QCsvFileWriter writer;

  SECTION("default")
  {
    REQUIRE( writer.filePath().isEmpty() );
  }

  SECTION("set and get")
  {
    writer.setFilePath( QLatin1String("test.csv") );
    REQUIRE( writer.filePath() == QLatin1String("test.csv") );
  }
}

TEST_CASE("fileEncoding")
{
  QCsvFileWriter writer;
  REQUIRE( writer.fileEncoding() == "UTF-8" );

  writer.setFileEncoding("ISO 8859-1");
  REQUIRE( writer.fileEncoding() == "ISO 8859-1" );
}

TEST_CASE("csvSettings")
{
  QCsvFileWriter writer;

  SECTION("default")
  {
    REQUIRE( writer.csvSettings().fieldSeparator() == ',' );
  }

  SECTION("set and get")
  {
    CsvGeneratorSettings settings;
    settings.setFieldSeparator(';');
    writer.setCsvSettings(settings);
    REQUIRE( writer.csvSettings().fieldSeparator() == ';' );
  }
}

TEST_CASE("openMode")
{
  QCsvFileWriter writer;

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

TEST_CASE("open_close")
{
  QTemporaryDir dir;
  REQUIRE( dir.isValid() );

  QCsvFileWriter writer;
  REQUIRE( !writer.isOpen() );

  const QString filePath = filePathFromDirAndFileName(dir, "test.csv");
  writer.setFilePath(filePath);
  REQUIRE( !writer.isOpen() );

  writer.open();
  REQUIRE( writer.isOpen() );

  writer.close();
  REQUIRE( !writer.isOpen() );
}
