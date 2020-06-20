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

QString qstringFromLatin1Char(char ch)
{
  return QString( QChar::fromLatin1(ch) );
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

TEST_CASE("alpha")
{
  using boost::spirit::qchar::alpha;

  QChar result;

  SECTION("A")
  {
    const QString source = QLatin1String("A");
    REQUIRE( parse(source, alpha, result) );
    REQUIRE( result == QLatin1Char('A') );
  }

  SECTION("2")
  {
    const QString source = QLatin1String("2");
    REQUIRE( !parse(source, alpha, result) );
  }
}

TEST_CASE("blank")
{
  using boost::spirit::qchar::blank;

  QChar result;

  SECTION("space")
  {
    const QString source = QLatin1String(" ");
    REQUIRE( parse(source, blank, result) );
  }

  SECTION("TAB")
  {
    const QString source = QLatin1String("\t");
    REQUIRE( parse(source, blank, result) );
  }

  SECTION("new line")
  {
    const QString source = QLatin1String("\n");
    REQUIRE( !parse(source, blank, result) );
  }

  SECTION("A")
  {
    const QString source = QLatin1String("A");
    REQUIRE( !parse(source, blank, result) );
  }
}

TEST_CASE("space")
{
  using boost::spirit::qchar::space;

  QChar result;

  SECTION("space")
  {
    const QString source = QLatin1String(" ");
    REQUIRE( parse(source, space, result) );
  }

  SECTION("TAB")
  {
    const QString source = QLatin1String("\t");
    REQUIRE( parse(source, space, result) );
  }

  SECTION("new line")
  {
    const QString source = QLatin1String("\n");
    REQUIRE( parse(source, space, result) );
  }

  SECTION("A")
  {
    const QString source = QLatin1String("A");
    REQUIRE( !parse(source, space, result) );
  }
}

TEST_CASE("cntrl")
{
  using boost::spirit::qchar::cntrl;

  QChar result;

  SECTION("NUL")
  {
    const QString source = qstringFromLatin1Char(0x00);
    REQUIRE( parse(source, cntrl, result) );
  }

  SECTION("SOH")
  {
    const QString source = qstringFromLatin1Char(0x01);
    REQUIRE( parse(source, cntrl, result) );
  }

  SECTION("STX")
  {
    const QString source = qstringFromLatin1Char(0x02);
    REQUIRE( parse(source, cntrl, result) );
  }

  SECTION("LF")
  {
    const QString source = qstringFromLatin1Char('\n');
    REQUIRE( parse(source, cntrl, result) );
  }

  SECTION("VT")
  {
    const QString source = qstringFromLatin1Char('\v');
    REQUIRE( parse(source, cntrl, result) );
  }

  SECTION("CR")
  {
    const QString source = qstringFromLatin1Char('\r');
    REQUIRE( parse(source, cntrl, result) );
  }

  SECTION("US")
  {
    const QString source = qstringFromLatin1Char(0x1F);
    REQUIRE( parse(source, cntrl, result) );
  }

  SECTION("DEL")
  {
    const QString source = qstringFromLatin1Char(0x7F);
    REQUIRE( parse(source, cntrl, result) );
  }

  SECTION("A")
  {
    const QString source = QLatin1String("A");
    REQUIRE( !parse(source, cntrl, result) );
  }
}

TEST_CASE("digit")
{
  using boost::spirit::qchar::digit;

  QChar result;

  SECTION("1")
  {
    const QString source = QLatin1String("1");
    REQUIRE( parse(source, digit, result) );
    REQUIRE( result == QLatin1Char('1') );
  }

  SECTION("9")
  {
    const QString source = QLatin1String("9");
    REQUIRE( parse(source, digit, result) );
    REQUIRE( result == QLatin1Char('9') );
  }

  SECTION("A")
  {
    const QString source = QLatin1String("A");
    REQUIRE( !parse(source, digit, result) );
  }
}

TEST_CASE("xdigit")
{
  using boost::spirit::qchar::xdigit;

  QChar result;

  SECTION("1")
  {
    const QString source = QLatin1String("1");
    REQUIRE( parse(source, xdigit, result) );
    REQUIRE( result == QLatin1Char('1') );
  }

  SECTION("9")
  {
    const QString source = QLatin1String("9");
    REQUIRE( parse(source, xdigit, result) );
    REQUIRE( result == QLatin1Char('9') );
  }

  SECTION("A")
  {
    const QString source = QLatin1String("A");
    REQUIRE( parse(source, xdigit, result) );
    REQUIRE( result == QLatin1Char('A') );
  }

  SECTION("a")
  {
    const QString source = QLatin1String("a");
    REQUIRE( parse(source, xdigit, result) );
    REQUIRE( result == QLatin1Char('a') );
  }

  SECTION("D")
  {
    const QString source = QLatin1String("D");
    REQUIRE( parse(source, xdigit, result) );
    REQUIRE( result == QLatin1Char('D') );
  }

  SECTION("d")
  {
    const QString source = QLatin1String("d");
    REQUIRE( parse(source, xdigit, result) );
    REQUIRE( result == QLatin1Char('d') );
  }

  SECTION("F")
  {
    const QString source = QLatin1String("F");
    REQUIRE( parse(source, xdigit, result) );
    REQUIRE( result == QLatin1Char('F') );
  }

  SECTION("f")
  {
    const QString source = QLatin1String("f");
    REQUIRE( parse(source, xdigit, result) );
    REQUIRE( result == QLatin1Char('f') );
  }

  SECTION("G")
  {
    const QString source = QLatin1String("G");
    REQUIRE( !parse(source, xdigit, result) );
  }

  SECTION("g")
  {
    const QString source = QLatin1String("g");
    REQUIRE( !parse(source, xdigit, result) );
  }

  SECTION("Z")
  {
    const QString source = QLatin1String("Z");
    REQUIRE( !parse(source, xdigit, result) );
  }

  SECTION("z")
  {
    const QString source = QLatin1String("z");
    REQUIRE( !parse(source, xdigit, result) );
  }
}

TEST_CASE("graph")
{
  using boost::spirit::qchar::graph;

  QChar result;

  SECTION("1")
  {
    const QString source = QLatin1String("1");
    REQUIRE( parse(source, graph, result) );
    REQUIRE( result == QLatin1Char('1') );
  }

  SECTION(" ")
  {
    const QString source = QLatin1String(" ");
    REQUIRE( !parse(source, graph, result) );
  }

  SECTION("A")
  {
    const QString source = QLatin1String("A");
    REQUIRE( parse(source, graph, result) );
    REQUIRE( result == QLatin1Char('A') );
  }
}

TEST_CASE("lower")
{
  using boost::spirit::qchar::lower;

  QChar result;

  SECTION("a")
  {
    const QString source = QLatin1String("a");
    REQUIRE( parse(source, lower, result) );
    REQUIRE( result == QLatin1Char('a') );
  }

  SECTION("A")
  {
    const QString source = QLatin1String("A");
    REQUIRE( !parse(source, lower, result) );
  }
}

TEST_CASE("upper")
{
  using boost::spirit::qchar::upper;

  QChar result;

  SECTION("A")
  {
    const QString source = QLatin1String("A");
    REQUIRE( parse(source, upper, result) );
    REQUIRE( result == QLatin1Char('A') );
  }

  SECTION("a")
  {
    const QString source = QLatin1String("a");
    REQUIRE( !parse(source, upper, result) );
  }
}

TEST_CASE("print")
{
  using boost::spirit::qchar::print;

  QChar result;

  SECTION("A")
  {
    const QString source = QLatin1String("A");
    REQUIRE( parse(source, print, result) );
    REQUIRE( result == QLatin1Char('A') );
  }

  SECTION("SOH")
  {
    const QString source = qstringFromLatin1Char(0x01);
    REQUIRE( !parse(source, print, result) );
  }
}

TEST_CASE("punct")
{
  using boost::spirit::qchar::punct;

  QChar result;

  SECTION("A")
  {
    const QString source = QLatin1String(".");
    REQUIRE( parse(source, punct, result) );
    REQUIRE( result == QLatin1Char('.') );
  }

  SECTION("A")
  {
    const QString source = QLatin1String("A");
    REQUIRE( !parse(source, punct, result) );
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
