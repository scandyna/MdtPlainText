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
#include "QTextFileInputConstIteratorSharedDataTestCommon.h"

TEST_CASE("Non existing codec")
{
  QTemporaryFile file;
  REQUIRE( file.open() );

  REQUIRE_THROWS_AS( QTextFileInputConstIteratorSharedData(&file, "SomeUnknownEncoding") , QTextCodecNotFoundError );
}

TEST_CASE("Read while closing file")
{
  QTemporaryFile file;
  REQUIRE( file.open() );
  const int rawBufferCapacity = 1;

  REQUIRE( writeTextFile(file, QLatin1String("ABCD")) );
  file.close();

  REQUIRE( openTextFileReadOnly(file) );
  QTextFileInputConstIteratorSharedData sd(&file, "UTF-8", rawBufferCapacity);
  REQUIRE( !sd.atEnd() );

  file.close();
  REQUIRE_THROWS_AS( sd.advance() , QFileReadError );
}
