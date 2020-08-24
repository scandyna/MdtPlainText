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
#include "Mdt/PlainText/QStringUnicodeConstIterator.h"
#include "Mdt/PlainText/BoostSpiritQStringContainer.h"
#include <boost/spirit/include/qi.hpp>
#include <QString>

using Mdt::PlainText::QStringUnicodeConstIterator;

template<typename Grammar>
bool parse(const QString & source, const Grammar & grammar, QString & destination)
{
    QStringUnicodeConstIterator first( source.cbegin(), source.cend() );
    QStringUnicodeConstIterator last( source.cend(), source.cend() );

  return boost::spirit::qi::parse(first, last, grammar, destination);
}

template<typename Grammar>
bool parse(const QString & source, const Grammar & grammar, QChar & destination)
{
    QStringUnicodeConstIterator first( source.cbegin(), source.cend() );
    QStringUnicodeConstIterator last( source.cend(), source.cend() );

  return boost::spirit::qi::parse(first, last, grammar, destination);
}

template<typename Grammar, typename Result>
bool parseNumber(const QString & source, const Grammar & grammar, Result & destination)
{
    QStringUnicodeConstIterator first( source.cbegin(), source.cend() );
    QStringUnicodeConstIterator last( source.cend(), source.cend() );

  return boost::spirit::qi::parse(first, last, grammar, destination);
}


TEST_CASE("qi_parser_int_")
{
  using boost::spirit::int_;

  int result;

  SECTION("24")
  {
    const QString source = QLatin1String("24");
    REQUIRE( parseNumber(source, int_, result) );
    REQUIRE( result == 24 );
  }
}

TEST_CASE("qi_parser_unicode_char_")
{
  using boost::spirit::unicode::char_;

  QString result;

  SECTION("ABC")
  {
    const QString source = QLatin1String("ABC");
    REQUIRE( parse(source, *char_, result) );
    REQUIRE( result == QLatin1String("ABC") );
  }

  SECTION("éöàäèü$£")
  {
    const QString source = QString::fromUtf8("éöàäèü$£");
    REQUIRE( parse(source, *char_, result) );
    REQUIRE( result == source );
  }

  SECTION("a𐐅ö")
  {
    const QString source = QString::fromUtf8("a𐐅ö");
    REQUIRE( parse(source, *char_, result) );
    REQUIRE( result == source );
  }

  SECTION("char_(A)")
  {
    const QString source = QLatin1String("A");
    QChar result;
    REQUIRE( parse(source, char_('A'), result) );
    REQUIRE( result == QLatin1Char('A') );
  }

  SECTION("char_(ö)")
  {
    const QString source = QString::fromUtf8("ö");
    QChar result;
    REQUIRE( parse(source, char_(U'\U000000F6'), result) );
    REQUIRE( result == QChar(0xF6) );
  }
}
