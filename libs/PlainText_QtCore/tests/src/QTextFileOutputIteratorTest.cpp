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
#include <type_traits>
#include <iterator>

TEST_CASE("construct")
{
  QTemporaryFile file;
  REQUIRE( openTextFileForWrite(file) );

  QTextFileOutputIterator it(&file, "UTF-8");
}

/*
 * Tests for LegacyIterator requirements
 */

static_assert( std::is_copy_constructible<QTextFileOutputIterator>::value , "" );
static_assert( std::is_destructible<QTextFileOutputIterator>::value , "" );

TEST_CASE("copy_construct")
{
  QTemporaryFile file;
  REQUIRE( openTextFileForWrite(file) );

  QTextFileOutputIterator a(&file, "UTF-8");

  QTextFileOutputIterator b(a);
}

/*
 * Tests for LegacyOutputIterator requirements
 */

static_assert( std::is_same< std::iterator_traits<QTextFileOutputIterator>::iterator_category, std::output_iterator_tag >::value, "" );

TEST_CASE("assign")
{
  QTemporaryFile file;
  REQUIRE( openTextFileForWrite(file) );
  QTextFileOutputIterator it(&file, "UTF-8");

  SECTION("A")
  {
    it = QLatin1Char('A');
    REQUIRE( readTextFileBack(file) == QLatin1String("A") );
  }

  SECTION("AB")
  {
    it = QLatin1Char('A');
    it = QLatin1Char('B');
    REQUIRE( readTextFileBack(file) == QLatin1String("AB") );
  }

  SECTION("ĵ")
  {
    it = U'\U00000135'; // ĵ
    REQUIRE( readTextFileBack(file) == QString::fromUtf8("ĵ") );
  }

  SECTION("aèöĵg")
  {
    it = u'a';
    it = U'\U000000E8'; // è
    it = U'\U000000F6'; // ö
    it = U'\U00000135'; // ĵ
    it = u'g';
    REQUIRE( readTextFileBack(file) == QString::fromUtf8("aèöĵg") );
  }
}

TEST_CASE("dereference")
{
  QTemporaryFile file;
  REQUIRE( openTextFileForWrite(file) );
  QTextFileOutputIterator it(&file, "UTF-8");

  SECTION("A")
  {
    *it = u'A';
    REQUIRE( readTextFileBack(file) == QLatin1String("A") );
  }
}

TEST_CASE("pre-increment")
{
  QTemporaryFile file;
  REQUIRE( openTextFileForWrite(file) );
  QTextFileOutputIterator it(&file, "UTF-8");

  SECTION("A")
  {
    *++it = u'A';
    REQUIRE( readTextFileBack(file) == QLatin1String("A") );
  }
}

TEST_CASE("post-increment")
{
  QTemporaryFile file;
  REQUIRE( openTextFileForWrite(file) );
  QTextFileOutputIterator it(&file, "UTF-8");

  SECTION("A")
  {
    *it++ = u'A';
    REQUIRE( readTextFileBack(file) == QLatin1String("A") );
  }
}
