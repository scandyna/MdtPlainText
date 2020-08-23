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
#include "Mdt/PlainText/QStringUnicodeView"
#include <QString>
#include <QLatin1String>
#include <boost/spirit/include/karma.hpp>
#include <string>
#include <iterator>

using Mdt::PlainText::QStringUnicodeView;

TEST_CASE("default_construct")
{
  QStringUnicodeView unicodeString;
  REQUIRE( unicodeString.begin() == unicodeString.end() );
}

TEST_CASE("assign_str")
{
  QString str;
  QStringUnicodeView unicodeString;

  SECTION("empty")
  {
    unicodeString = str;
    REQUIRE( unicodeString.toQString().isEmpty() );
  }

  SECTION("A then empty")
  {
    str = QLatin1String("A");
    unicodeString = str;
    REQUIRE( unicodeString.toQString() == QLatin1String("A") );

    str.clear();
    unicodeString = str;
    REQUIRE( unicodeString.toQString().isEmpty() );
  }

  SECTION("A then B")
  {
    str = QLatin1String("A");
    unicodeString = str;
    REQUIRE( unicodeString.toQString() == QLatin1String("A") );

    str = QLatin1String("B");
    unicodeString = str;
    REQUIRE( unicodeString.toQString() == QLatin1String("B") );
  }
}

TEST_CASE("toQString")
{
  QString str;

  SECTION("empty")
  {
    QStringUnicodeView c(str);
    REQUIRE( c.toQString().isEmpty() );
  }

  SECTION("A")
  {
    str = QLatin1String("A");
    QStringUnicodeView c(str);
    REQUIRE( c.toQString() == QLatin1String("A") );
  }

  SECTION("ABC")
  {
    str = QLatin1String("ABC");
    QStringUnicodeView c(str);
    REQUIRE( c.toQString() == QLatin1String("ABC") );
  }

  SECTION("𐐅")
  {
    str = QString::fromUtf8("𐐅");
    QStringUnicodeView c(str);
    REQUIRE( c.toQString() == QString::fromUtf8("𐐅") );
  }
}
