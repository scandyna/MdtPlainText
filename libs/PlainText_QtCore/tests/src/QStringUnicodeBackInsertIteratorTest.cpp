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
#include "catch2/catch.hpp"
#include "Mdt/PlainText/QStringUnicodeBackInsertIterator.h"
#include <QString>
#include <QLatin1String>
#include <type_traits>
#include <iterator>

using Mdt::PlainText::QStringUnicodeBackInsertIterator;

TEST_CASE("construct")
{
  QString str;
  QStringUnicodeBackInsertIterator it(str);
//   Q_UNUSED(it);
}

/*
 * Tests for LegacyIterator requirements
 */

static_assert( std::is_copy_constructible<QStringUnicodeBackInsertIterator>::value , "" );
static_assert( std::is_destructible<QStringUnicodeBackInsertIterator>::value , "" );

/*
 * Tests for LegacyOutputIterator requirements
 */

TEST_CASE("assign")
{
  QString str;
  QStringUnicodeBackInsertIterator it(str);

  SECTION("A")
  {
    it = U'A';
    REQUIRE( str == QLatin1String("A") );
  }

  SECTION("AB")
  {
    it = U'A';
    it = U'B';
    REQUIRE( str == QLatin1String("AB") );
  }

  SECTION("ĵ")
  {
    it = U'ĵ';
    REQUIRE( str == QString::fromUtf8("ĵ") );
  }

  SECTION("𐐅")
  {
    it = U'𐐅';
    REQUIRE( str == QString::fromUtf8("𐐅") );
  }

  SECTION("A𐐅")
  {
    it = U'A';
    it = U'𐐅';
    REQUIRE( str == QString::fromUtf8("A𐐅") );
  }

  SECTION("𐐅A")
  {
    it = U'𐐅';
    it = U'A';
    REQUIRE( str == QString::fromUtf8("𐐅A") );
  }
}

TEST_CASE("dereference")
{
  QString str;
  QStringUnicodeBackInsertIterator it(str);

  SECTION("A")
  {
    *it = U'A';
    REQUIRE( str == QLatin1String("A") );
  }
}

TEST_CASE("pre-increment")
{
  QString str;
  QStringUnicodeBackInsertIterator it(str);

  SECTION("A")
  {
    *++it = U'A';
    REQUIRE( str == QLatin1String("A") );
  }
}

TEST_CASE("post-increment")
{
  QString str;
  QStringUnicodeBackInsertIterator it(str);

  SECTION("A")
  {
    *it++ = U'A';
    REQUIRE( str == QLatin1String("A") );
  }
}
