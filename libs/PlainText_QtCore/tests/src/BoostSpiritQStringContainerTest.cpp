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
#include "Mdt/PlainText/BoostSpiritQStringContainer.h"
#include "Mdt/PlainText/BoostSpiritKarmaQStringContainer.h"
#include <QChar>
#include <QLatin1Char>
#include <QString>
#include <QLatin1String>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <string>

template<typename Rule>
bool parseFromStdString(const std::string & source, const Rule & rule, QString & destination)
{
  return boost::spirit::qi::parse(source.cbegin(), source.cend(), rule, destination);
}

template<typename Rule>
bool parseFromStdu32String(const std::u32string & source, const Rule & rule, QString & destination)
{
  return boost::spirit::qi::parse(source.cbegin(), source.cend(), rule, destination);
}

template<typename Rule>
bool generateToStdString(const QString & source, const Rule & rule, std::string & destination)
{
  const Mdt::PlainText::BoostSpiritKarmaQStringContainer sourceContainer(source);

  return boost::spirit::karma::generate(std::back_inserter(destination), rule, sourceContainer);
}

template<typename Rule>
bool generateToStdu32String(const QString & source, const Rule & rule, std::u32string & destination)
{
  const Mdt::PlainText::BoostSpiritKarmaQStringContainer sourceContainer(source);

  return boost::spirit::karma::generate(std::back_inserter(destination), rule, sourceContainer);
}


TEST_CASE("qi_parse_standard_char_")
{
  using boost::spirit::standard::char_;

  QString result;

  SECTION("A")
  {
    REQUIRE( parseFromStdString("A", *char_, result) );
    REQUIRE( result == QLatin1String("A") );
  }

  SECTION("AB")
  {
    REQUIRE( parseFromStdString("AB", *char_, result) );
    REQUIRE( result == QLatin1String("AB") );
  }

  SECTION("ABC")
  {
    REQUIRE( parseFromStdString("ABC", *char_, result) );
    REQUIRE( result == QLatin1String("ABC") );
  }
}

TEST_CASE("karma_generate_standard_char_")
{
  using boost::spirit::standard::char_;

  std::string result;

  SECTION("A")
  {
    REQUIRE( generateToStdString(QLatin1String("A"), *char_, result) );
    REQUIRE( result == "A" );
  }

  SECTION("AB")
  {
    REQUIRE( generateToStdString(QLatin1String("AB"), *char_, result) );
    REQUIRE( result == "AB" );
  }

  SECTION("ABC")
  {
    REQUIRE( generateToStdString(QLatin1String("ABC"), *char_, result) );
    REQUIRE( result == "ABC" );
  }
}

TEST_CASE("qi_parse_unicode_char_")
{
  using boost::spirit::unicode::char_;

  QString result;

  SECTION("A")
  {
    REQUIRE( parseFromStdu32String(U"A", *char_, result) );
    REQUIRE( result == QLatin1String("A") );
  }

  SECTION("ö")
  {
    REQUIRE( parseFromStdu32String(U"\U000000f6", *char_, result) );
    REQUIRE( result == QString::fromUtf8("ö") );
  }

  SECTION("ĵ")
  {
    REQUIRE( parseFromStdu32String(U"\U00000135", *char_, result) );
    REQUIRE( result == QString::fromUtf8("ĵ") );
  }

  SECTION("�")
  {
    REQUIRE( parseFromStdu32String(U"\U0000fffd", *char_, result) );
    REQUIRE( result == QString::fromUtf8("�") );
  }

  SECTION("𐀀")
  {
    REQUIRE( parseFromStdu32String(U"\U00010000", *char_, result) );
    REQUIRE( result == QString::fromUtf8("𐀀") );
  }

  SECTION("𐐅")
  {
    REQUIRE( parseFromStdu32String(U"\U00010405", *char_, result) );
    REQUIRE( result == QString::fromUtf8("𐐅") );
  }
}

TEST_CASE("karma_generate_unicode_char_")
{
  using boost::spirit::unicode::char_;

  std::u32string result;

  SECTION("A")
  {
    REQUIRE( generateToStdu32String(QLatin1String("A"), *char_, result) );
    REQUIRE( result == U"A" );
  }

  SECTION("ö")
  {
    REQUIRE( generateToStdu32String(QString::fromUtf8("ö"), *char_, result) );
    REQUIRE( result == U"\U000000f6" );
  }

  SECTION("ĵ")
  {
    REQUIRE( generateToStdu32String(QString::fromUtf8("ĵ"), *char_, result) );
    REQUIRE( result == U"\U00000135" );
  }

  SECTION("�")
  {
    REQUIRE( generateToStdu32String(QString::fromUtf8("�"), *char_, result) );
    REQUIRE( result == U"\U0000fffd" );
  }

  SECTION("𐀀")
  {
    REQUIRE( generateToStdu32String(QString::fromUtf8("𐀀"), *char_, result) );
    REQUIRE( result == U"\U00010000" );
  }

  SECTION("𐐅")
  {
    REQUIRE( generateToStdu32String(QString::fromUtf8("𐐅"), *char_, result) );
    REQUIRE( result == U"\U00010405" );
  }
}
