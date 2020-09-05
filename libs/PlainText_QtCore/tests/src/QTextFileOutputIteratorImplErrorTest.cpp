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
#include "QTextFileOutputIteratorTestCommon.h"
#include "Mdt/PlainText/QTextFileOutputIteratorImpl.h"

using namespace Mdt::PlainText;

TEST_CASE("Non existing codec")
{
  QTemporaryFile file;
  REQUIRE( openTextFileForWrite(file) );

  REQUIRE_THROWS_AS( QTextFileOutputIteratorImpl(&file, "SomeUnknownEncoding") , QTextCodecNotFoundError );
}

TEST_CASE("Close file while writing")
{
  QTemporaryFile file;
  REQUIRE( openTextFileForWrite(file) );

  QTextFileOutputIteratorImpl it(&file, "UTF-8");

  file.close();
  REQUIRE_THROWS_AS( it.put(u'A'), QFileWriteError );
}
