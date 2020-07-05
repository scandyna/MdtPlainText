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
#include <boost/spirit/include/qi.hpp>
#include <string>

template<typename Grammar>
bool parseFromStdString(const std::string & source, const Grammar & grammar, QString & destination)
{
  return boost::spirit::qi::parse(source.cbegin(), source.cend(), grammar, destination);
}

// template<typename Grammar>
// bool parse(const std::string & source, const Grammar & grammar, QChar & destination)
// {
//   return boost::spirit::qi::parse(source.cbegin(), source.cend(), grammar, destination);
// }

template<typename Grammar>
bool parseFromStdu32String(const std::u32string & source, const Grammar & grammar, QString & destination)
{
  return boost::spirit::qi::parse(source.cbegin(), source.cend(), grammar, destination);
}

// TEST_CASE("QCharFromUnit32")
// {
//   using namespace Mdt::PlainText::Impl;
// 
//   SECTION("A")
//   {
//     uint32_t code = 'A';
//     REQUIRE( lowCharFromUint32UnicodePoint(code) == QLatin1Char('A') );
//     REQUIRE( highCharFromUint32UnicodePoint(code).isNull() );
//   }
// 
//   SECTION("�")
//   {
//     uint32_t code = 0x0000fffd;
//     REQUIRE( highCharFromUint32UnicodePoint(code) == QChar(0x0000) );
//     REQUIRE( lowCharFromUint32UnicodePoint(code) == QChar(0xfffd) );
//   }
// 
//   SECTION("𐀀")
//   {
//     uint32_t code = 0x00010000;
//     REQUIRE( highCharFromUint32UnicodePoint(code) == QChar(0x0001) );
//     REQUIRE( lowCharFromUint32UnicodePoint(code) == QChar(0x0000) );
//   }
// 
//   SECTION("𐐅")
//   {
//     uint32_t code = 0x00010405;
//     REQUIRE( highCharFromUint32UnicodePoint(code) == QChar(0x0001) );
//     REQUIRE( lowCharFromUint32UnicodePoint(code) == QChar(0x0405) );
//   }
// }

TEST_CASE("unicode_char_")
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

// TEST_CASE("standard_char_")
// {
//   using boost::spirit::standard::char_;
// 
//   SECTION("char_")
//   {
//     QChar result;
//     REQUIRE( parse("A", char_, result) );
//     REQUIRE( result == QLatin1Char('A') );
//   }
// }

// TEST_CASE("unicode_char_")
// {
//   using boost::spirit::unicode::char_;
// 
//   SECTION("char_")
//   {
//     QChar result;
//     REQUIRE( parse("A", char_, result) );
//     REQUIRE( result == QLatin1Char('A') );
//   }
// }

TEST_CASE("standard_char_")
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
