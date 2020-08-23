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
#include "QStringListUnicodeViewTestCommon.h"

static_assert( std::is_copy_constructible<QStringListUnicodeView>::value , "" );
static_assert( std::is_copy_assignable<QStringListUnicodeView>::value , "" );
static_assert( std::is_destructible<QStringListUnicodeView>::value , "" );

TEST_CASE("construct")
{
  const QStringList stringList = qStringListFromStdStringList({"A","bcd"});
  const QStringListUnicodeView unicodeStringList(stringList);
  REQUIRE( unicodeStringList.size() == 2 );
}

TEST_CASE("at")
{
  QStringList stringList;

  SECTION("A")
  {
    stringList = qStringListFromStdStringList({"A"});
    const QStringListUnicodeView unicodeStringList(stringList);
    REQUIRE( unicodeStringList.size() == 1 );
    REQUIRE( unicodeStringViewEqualsLatin1String(unicodeStringList.at(0), "A") );
  }

  REQUIRE(false);
}

TEST_CASE("operator_square_bracket")
{
  REQUIRE(false);
}

TEST_CASE("Range_for")
{
  REQUIRE(false);
}

TEST_CASE("std_copy")
{
  REQUIRE(false);
}
