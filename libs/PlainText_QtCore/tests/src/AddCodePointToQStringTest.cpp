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
#include "Mdt/PlainText/Impl/AddCodePointToQString.h"
#include <QString>
#include <QLatin1String>

using Mdt::PlainText::Impl::addCodePointToQString;

TEST_CASE("addCodePointToQString")
{
  QString str;

  SECTION("A")
  {
    addCodePointToQString(U'A', str);
    REQUIRE( str == QLatin1String("A") );
  }

  SECTION("AB")
  {
    addCodePointToQString(U'A', str);
    addCodePointToQString(U'B', str);
    REQUIRE( str == QLatin1String("AB") );
  }

  SECTION("ABC")
  {
    addCodePointToQString(U'A', str);
    addCodePointToQString(U'B', str);
    addCodePointToQString(U'C', str);
    REQUIRE( str == QLatin1String("ABC") );
  }

  SECTION("ABCD")
  {
    addCodePointToQString(U'A', str);
    addCodePointToQString(U'B', str);
    addCodePointToQString(U'C', str);
    addCodePointToQString(U'D', str);
    REQUIRE( str == QLatin1String("ABCD") );
  }

  SECTION("ö")
  {
    addCodePointToQString(U'\U000000F6', str);
    REQUIRE( str == QString::fromUtf8("ö") );
  }

  SECTION("ĵ")
  {
    addCodePointToQString(U'\U00000135', str);
    REQUIRE( str == QString::fromUtf8("ĵ") );
  }

  SECTION("�")
  {
    addCodePointToQString(U'\U0000FFFD', str);
    REQUIRE( str == QString::fromUtf8("�") );
  }

  SECTION("𐀀")
  {
    addCodePointToQString(U'\U00010000', str);
    REQUIRE( str == QString::fromUtf8("𐀀") );
  }

  SECTION("𐐅")
  {
    addCodePointToQString(U'\U00010405', str);
    REQUIRE( str == QString::fromUtf8("𐐅") );
  }

  SECTION("A𐐅")
  {
    addCodePointToQString(U'A', str);
    addCodePointToQString(U'\U00010405', str);
    REQUIRE( str == QString::fromUtf8("A𐐅") );
  }

  SECTION("𐐅A")
  {
    addCodePointToQString(U'\U00010405', str);
    addCodePointToQString(U'A', str);
    REQUIRE( str == QString::fromUtf8("𐐅A") );
  }

  SECTION("𝛀")
  {
    addCodePointToQString(U'\U0001D6C0', str);
    REQUIRE( str == QString::fromUtf8("𝛀") );
  }
}
