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

using Mdt::PlainText::QTextFileOutputIteratorImpl;

TEST_CASE("Check UTF-8 support")
{
  REQUIRE( QTextCodec::codecForName("UTF-8") != nullptr );
}

TEST_CASE("construct")
{
  QTemporaryFile file;
  REQUIRE( openTextFileForWrite(file) );

  QTextFileOutputIteratorImpl it(&file, "UTF-8");
}

TEST_CASE("put")
{
  QTemporaryFile file;
  REQUIRE( openTextFileForWrite(file) );
  QTextFileOutputIteratorImpl it(&file, "UTF-8");

  SECTION("A")
  {
    it.put(u'A');
    REQUIRE( readTextFileBack(file) == QLatin1String("A") );
  }

  SECTION("AB")
  {
    it.put(u'A');
    it.put(u'B');
    REQUIRE( readTextFileBack(file) == QLatin1String("AB") );
  }

  SECTION("ABC")
  {
    it.put(u'A');
    it.put(u'B');
    it.put(u'C');
    REQUIRE( readTextFileBack(file) == QLatin1String("ABC") );
  }

  SECTION("ĵ")
  {
    it.put(u'ĵ');
    REQUIRE( readTextFileBack(file) == QString::fromUtf8("ĵ") );
  }

  SECTION("aèöĵg")
  {
    it.put(u'a');
    it.put(u'è');
    it.put(u'ö');
    it.put(u'ĵ');
    it.put(u'g');
    REQUIRE( readTextFileBack(file) == QString::fromUtf8("aèöĵg") );
  }
}
