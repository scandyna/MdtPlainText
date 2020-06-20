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
#include "Mdt/PlainText/BoostSpiritQStringEncoding.h"
#include "Mdt/PlainText/BoostSpiritQStringContainer.h"
#include <boost/spirit/include/qi.hpp>
#include <QString>
#include <QLatin1String>
// #include <string>

template<typename Grammar>
bool parse(const QString & source, const Grammar & grammar, QString & destination)
{
  return boost::spirit::qi::parse(source.cbegin(), source.cend(), grammar, destination);
}

template<typename Grammar>
bool parse(const QString & source, const Grammar & grammar, QChar & destination)
{
  return boost::spirit::qi::parse(source.cbegin(), source.cend(), grammar, destination);
}


TEST_CASE("char_")
{
  using boost::spirit::qchar::char_;

  QChar result;

  REQUIRE( parse( QLatin1String("A"), char_, result ) );
  REQUIRE( result == QLatin1Char('A') );
}

TEST_CASE("char_(ch)")
{
  using boost::spirit::qchar::char_;

  QChar result;
  const QString source = QLatin1String("ABCD");

  SECTION("A")
  {
    REQUIRE( parse(source, char_(QLatin1Char('A')), result) );
    REQUIRE( result == QLatin1Char('A') );
  }

  SECTION("Z")
  {
    REQUIRE( !parse(source, char_(QLatin1Char('Z')), result) );
  }
}

TEST_CASE("char_(first, last)")
{
  using boost::spirit::qchar::char_;

  QChar result;
  const QString source = QLatin1String("ABCD");

  SECTION("A-Z")
  {
    REQUIRE( parse(source, char_(QLatin1Char('A'), QLatin1Char('Z')), result) );
    REQUIRE( result == QLatin1Char('A') );
  }

  SECTION("0-9")
  {
    REQUIRE( !parse(source, char_(QLatin1Char('0'), QLatin1Char('9')), result) );
  }
}

/** \todo enable once possible
 *
TEST_CASE("char_(def)")
{
  using boost::spirit::qchar::char_;

  QChar result;
  const QString source = QLatin1String("ABCD");

  SECTION("a-zA-Z (QString)")
  {
    const QString def = QLatin1String("a-zA-Z");
    REQUIRE( parse(source, char_(def), result) );
    REQUIRE( result == QLatin1Char('A') );
  }

  SECTION("a-zA-Z (QLatin1String)")
  {
    REQUIRE( parse(source, char_(QLatin1String("a-zA-Z")), result) );
    REQUIRE( result == QLatin1Char('A') );
  }

  SECTION("0-9")
  {
    REQUIRE( !parse(source, char_(QLatin1String("0-9")), result) );
  }
}
*/

/** \todo enable once possible
TEST_CASE("lit(ch)")
{
  using boost::spirit::lit;

  QChar result;
  const QString source = QLatin1String("ABCD");

  SECTION("A")
  {
    REQUIRE( parse(source, lit(QLatin1Char('A')), result) );
  }

  SECTION("Z")
  {
    REQUIRE( !parse(source, lit(QLatin1Char('Z')), result) );
  }
}
*/

TEST_CASE("alnum")
{
  using boost::spirit::qchar::alnum;

  QChar result;

  SECTION("A")
  {
    const QString source = QLatin1String("A");
    REQUIRE( parse(source, alnum, result) );
    REQUIRE( result == QLatin1Char('A') );
  }

  SECTION("!")
  {
    const QString source = QLatin1String("!");
    REQUIRE( !parse(source, alnum, result) );
  }
}

TEST_CASE("*char_")
{
  using boost::spirit::qchar::char_;

  QString result;

  SECTION("A")
  {
    REQUIRE( parse( QLatin1String("A"), *char_, result ) );
    REQUIRE( result == QLatin1String("A") );
  }

  SECTION("AB")
  {
    REQUIRE( parse( QLatin1String("AB"), *char_, result ) );
    REQUIRE( result == QLatin1String("AB") );
  }

  SECTION("ABC")
  {
    REQUIRE( parse( QLatin1String("ABC"), *char_, result ) );
    REQUIRE( result == QLatin1String("ABC") );
  }
}
