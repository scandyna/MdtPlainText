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
#include "Mdt/PlainText/QTextFileUnicodeOutputIterator.h"
#include <type_traits>
#include <iterator>

using Mdt::PlainText::QTextFileUnicodeOutputIterator;

TEST_CASE("construct")
{
  QTemporaryFile file;
  REQUIRE( openTextFileForWrite(file) );

  QTextFileUnicodeOutputIterator it(file, "UTF-8");
}

/*
 * Tests for LegacyIterator requirements
 */

static_assert( std::is_copy_constructible<QTextFileUnicodeOutputIterator>::value , "" );
static_assert( std::is_destructible<QTextFileUnicodeOutputIterator>::value , "" );

TEST_CASE("copy_construct")
{
  QTemporaryFile file;
  REQUIRE( openTextFileForWrite(file) );

  QTextFileUnicodeOutputIterator a(file, "UTF-8");

  QTextFileUnicodeOutputIterator b(a);
}

/*
 * Tests for LegacyOutputIterator requirements
 */

static_assert( std::is_same< std::iterator_traits<QTextFileUnicodeOutputIterator>::iterator_category, std::output_iterator_tag >::value, "" );

TEST_CASE("assign")
{
  QTemporaryFile file;
  REQUIRE( openTextFileForWrite(file) );
  QTextFileUnicodeOutputIterator it(file, "UTF-8");

  SECTION("A")
  {
    it = U'A';
    REQUIRE( readTextFileBack(file) == QLatin1String("A") );
  }

  SECTION("AB")
  {
    it = U'A';
    it = U'B';
    REQUIRE( readTextFileBack(file) == QLatin1String("AB") );
  }

  SECTION("ĵ")
  {
    it = U'\U00000135'; // ĵ
    REQUIRE( readTextFileBack(file) == QString::fromUtf8("ĵ") );
  }

  SECTION("aèöĵg")
  {
    it = U'a';
    it = U'\U000000E8'; // è
    it = U'\U000000F6'; // ö
    it = U'\U00000135'; // ĵ
    it = U'g';
    REQUIRE( readTextFileBack(file) == QString::fromUtf8("aèöĵg") );
  }

  SECTION("𐐅")
  {
    it = U'\U00010405'; // 𐐅
    REQUIRE( readTextFileBack(file) == QString::fromUtf8("𐐅") );
  }

  SECTION("A𐐅")
  {
    it = U'A';
    it = U'\U00010405'; // 𐐅
    REQUIRE( readTextFileBack(file) == QString::fromUtf8("A𐐅") );
  }

  SECTION("𐐅A")
  {
    it = U'\U00010405'; // 𐐅
    it = U'A';
    REQUIRE( readTextFileBack(file) == QString::fromUtf8("𐐅A") );
  }
}

TEST_CASE("dereference")
{
  QTemporaryFile file;
  REQUIRE( openTextFileForWrite(file) );
  QTextFileUnicodeOutputIterator it(file, "UTF-8");

  SECTION("A")
  {
    *it = U'A';
    REQUIRE( readTextFileBack(file) == QLatin1String("A") );
  }
}

TEST_CASE("pre-increment")
{
  QTemporaryFile file;
  REQUIRE( openTextFileForWrite(file) );
  QTextFileUnicodeOutputIterator it(file, "UTF-8");

  SECTION("A")
  {
    *++it = U'A';
    REQUIRE( readTextFileBack(file) == QLatin1String("A") );
  }
}

TEST_CASE("post-increment")
{
  QTemporaryFile file;
  REQUIRE( openTextFileForWrite(file) );
  QTextFileUnicodeOutputIterator it(file, "UTF-8");

  SECTION("A")
  {
    *it++ = U'A';
    REQUIRE( readTextFileBack(file) == QLatin1String("A") );
  }
}
