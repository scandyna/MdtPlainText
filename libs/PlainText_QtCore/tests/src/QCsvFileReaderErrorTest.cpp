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

TEST_CASE("open")
{
  QCsvFileReader reader;

  SECTION("File not exists")
  {
    reader.setFilePath( QLatin1String("/some/non/exising/file.csv") );

    REQUIRE_THROWS_AS( reader.open(), QFileOpenError );
  }

  SECTION("Path refers to a directory")
  {
    QTemporaryDir dir;
    REQUIRE( dir.isValid() );

    setDirectoryPathToReader(dir, reader);

    REQUIRE_THROWS_AS( reader.open(), QFileOpenError );
  }

  SECTION("File encoding not supported")
  {
    QTemporaryFile file;
    REQUIRE( file.open() );

    REQUIRE( writeTextFile(file, QLatin1String("A,B,C")) );
    file.close();

    setFilePathToReader(file, reader);
    reader.setFileEncoding("SomeUnknownEncoding");
    REQUIRE_THROWS_AS( reader.open(), QTextCodecNotFoundError );
  }
}
