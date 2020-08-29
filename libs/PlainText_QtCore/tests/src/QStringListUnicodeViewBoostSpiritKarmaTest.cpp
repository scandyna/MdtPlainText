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
#include <boost/spirit/include/karma.hpp>

template<typename FieldColumnRule>
bool generateToStdString(const QStringList & record, const FieldColumnRule & fieldColumn, std::string & destination)
{
  const QStringListUnicodeView sourceContainer(record);

  boost::spirit::karma::rule<std::back_insert_iterator<std::string>, QStringListUnicodeView()> csvRecord;
  csvRecord = fieldColumn % ',';

  return boost::spirit::karma::generate(std::back_inserter(destination), csvRecord, sourceContainer);
}

template<typename FieldColumnRule>
bool generateToStdu32String(const QStringList & record, const FieldColumnRule & fieldColumn, std::u32string & destination)
{
  const QStringListUnicodeView sourceContainer(record);

  boost::spirit::karma::rule<std::back_insert_iterator<std::u32string>, QStringListUnicodeView()> csvRecord;
  csvRecord = fieldColumn % ',';

  return boost::spirit::karma::generate(std::back_inserter(destination), csvRecord, sourceContainer);
}


TEST_CASE("standard_char_")
{
  using boost::spirit::standard::char_;

  QStringList record;
  std::string result;

  SECTION("A")
  {
    REQUIRE( generateToStdString({QLatin1String("A")}, *char_, result) );
    REQUIRE( result == "A" );
  }

  SECTION("A|B")
  {
    record = qStringListFromStdStringList({"A","B"});
    REQUIRE( generateToStdString(record, *char_, result) );
    REQUIRE( result == "A,B" );
  }

  SECTION("AB|C|DE")
  {
    record = qStringListFromStdStringList({"AB","C","DE"});
    REQUIRE( generateToStdString(record, *char_, result) );
    REQUIRE( result == "AB,C,DE" );
  }
}

TEST_CASE("unicode_char_")
{
  using boost::spirit::unicode::char_;

  QStringList record;
  std::u32string result;

  SECTION("A|B")
  {
    record = qStringListFromStdStringList({"A","B"});
    REQUIRE( generateToStdu32String(record, *char_, result) );
    REQUIRE( result == U"A,B" );
  }

  SECTION("éö|àäè|ü$£")
  {
    record = qStringListFromStdStringList({"éö","àäè","ü$£"});
    REQUIRE( generateToStdu32String(record, *char_, result) );
    REQUIRE( result == U"éö,àäè,ü$£" );
  }

  SECTION("a|𐐅ö")
  {
    record = qStringListFromStdStringList({"a","𐐅ö"});
    REQUIRE( generateToStdu32String(record, *char_, result) );
    REQUIRE( result == U"a,𐐅ö" );
  }
}

TEST_CASE("Sequence")
{
  using boost::spirit::unicode::char_;
  using boost::spirit::lit;

  QStringList record;
  std::u32string result;

  SECTION("*char_ << char_")
  {
    SECTION("A << B")
    {
      record = qStringListFromStdStringList({"A"});
      REQUIRE( generateToStdu32String(record, *char_ << lit('B'), result) );
      REQUIRE( result == U"AB" );
    }
  }
}
