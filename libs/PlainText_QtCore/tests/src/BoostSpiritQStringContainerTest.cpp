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
#include "TestCommon.h"
#include "Mdt/PlainText/BoostSpiritQStringContainer.h"
#include <QChar>
#include <QLatin1Char>
#include <QString>
#include <QLatin1String>
#include <string>

template<typename Grammar>
bool parse(const std::string & source, const Grammar & grammar, QString & destination)
{
  return boost::spirit::qi::parse(source.cbegin(), source.cend(), grammar, destination);
}

template<typename Grammar>
bool parse(const std::string & source, const Grammar & grammar, QChar & destination)
{
  return boost::spirit::qi::parse(source.cbegin(), source.cend(), grammar, destination);
}

TEST_CASE("standard_char_")
{
  using boost::spirit::standard::char_;

  SECTION("char_")
  {
    QChar result;
    REQUIRE( parse("A", char_, result) );
    REQUIRE( result == QLatin1Char('A') );
  }
}

TEST_CASE("from_std_string")
{
  using boost::spirit::standard::char_;

  QString result;

  SECTION("A")
  {
    REQUIRE( parse("A", *char_, result) );
    REQUIRE( result == QLatin1String("A") );
  }

  SECTION("AB")
  {
    REQUIRE( parse("AB", *char_, result) );
    REQUIRE( result == QLatin1String("AB") );
  }

  SECTION("ABC")
  {
    REQUIRE( parse("ABC", *char_, result) );
    REQUIRE( result == QLatin1String("ABC") );
  }
}


TEST_CASE("from_std_wstring")
{
  REQUIRE( false );
}
