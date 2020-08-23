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
#include "Mdt/PlainText/QStringContainerUnicodeConstIterator.h"
#include "Mdt/PlainText/QStringUnicodeView"
#include <QStringList>
#include <QString>
#include <string>
#include <vector>
#include <type_traits>

using Mdt::PlainText::QStringUnicodeView;
using Mdt::PlainText::QStringContainerUnicodeConstIterator;
using QStringListUnicodeConstIterator = QStringContainerUnicodeConstIterator<QStringList::const_iterator>;


QStringList qStringListFromStdStringList(const std::vector<std::string> & stdStringList)
{
  QStringList stringList;

  for(const std::string & str : stdStringList){
    stringList.append( QString::fromStdString(str) );
  }

  return stringList;
}

bool unicodeStringViewEqualsStdString(const QStringUnicodeView & s1, const std::string & s2)
{
  return s1.toQString().toStdString() == s2;
}


TEST_CASE("construct")
{
  QStringList stringList;

  SECTION("From empty list")
  {
    QStringListUnicodeConstIterator first( stringList.cbegin() );
    QStringListUnicodeConstIterator last( stringList.cend() );
    REQUIRE( first == last );
  }

  SECTION("ABC")
  {
    stringList = qStringListFromStdStringList({"ABC"});
    QStringListUnicodeConstIterator it( stringList.cbegin() );
    REQUIRE( unicodeStringViewEqualsStdString( *it, "ABC" ) );
  }
}

/*
 * Tests for LegacyIterator requirements
 */

static_assert( std::is_copy_constructible<QStringListUnicodeConstIterator>::value , "" );
static_assert( std::is_copy_assignable<QStringListUnicodeConstIterator>::value , "" );
static_assert( std::is_destructible<QStringListUnicodeConstIterator>::value , "" );

TEST_CASE("copy_construct")
{
  QStringList stringList;

  SECTION("empty list")
  {
    QStringListUnicodeConstIterator a( stringList.cbegin() );
    QStringListUnicodeConstIterator b(a);
    REQUIRE( a == b );
  }

  SECTION("A")
  {
    stringList = qStringListFromStdStringList({"A"});
    QStringListUnicodeConstIterator a( stringList.cbegin() );
    QStringListUnicodeConstIterator b(a);
    REQUIRE( unicodeStringViewEqualsStdString( *b, "A" ) );
  }
}

TEST_CASE("assign")
{
  QStringList stringList = qStringListFromStdStringList({"A"});
  QStringListUnicodeConstIterator b;

  QStringListUnicodeConstIterator a( stringList.cbegin() );
  REQUIRE( unicodeStringViewEqualsStdString( *a, "A" ) );

  b = a;
  REQUIRE( unicodeStringViewEqualsStdString( *b, "A" ) );
}

TEST_CASE("dereference")
{
  QStringList stringList = qStringListFromStdStringList({"A"});
  QStringListUnicodeConstIterator it( stringList.cbegin() );

  REQUIRE( unicodeStringViewEqualsStdString( *it, "A" ) );
}

TEST_CASE("pre-increment")
{
  QStringList stringList;

  SECTION("AB|C")
  {
    stringList = qStringListFromStdStringList({"AB","C"});
    QStringListUnicodeConstIterator it( stringList.cbegin() );
    REQUIRE( unicodeStringViewEqualsStdString( *it, "AB" ) );

    ++it;
    REQUIRE( unicodeStringViewEqualsStdString( *it, "C" ) );
  }
}

/*
 * Tests for LegacyInputIterator requirements
 */

TEST_CASE("comparison")
{
  QStringList stringList = qStringListFromStdStringList({"A"});
  QStringListUnicodeConstIterator a( stringList.cbegin() );
  QStringListUnicodeConstIterator b( stringList.cbegin() );

  REQUIRE( a == b );
  REQUIRE( !(a != b) );
}

TEST_CASE("post-increment")
{
  QStringList stringList;

  SECTION("A|BC")
  {
    stringList = qStringListFromStdStringList({"A","BC"});
    QStringListUnicodeConstIterator it( stringList.cbegin() );
    REQUIRE( unicodeStringViewEqualsStdString( *it, "A" ) );

    it++;
    REQUIRE( unicodeStringViewEqualsStdString( *it, "BC" ) );
  }
}

/*
 * Tests for LegacyForwardIterator requirements
 */

static_assert( std::is_default_constructible<QStringListUnicodeConstIterator>::value , "" );

TEST_CASE("default_construct")
{
  QStringList stringList = qStringListFromStdStringList({"A"});
  QStringListUnicodeConstIterator a( stringList.cbegin() );
  QStringListUnicodeConstIterator b;

  REQUIRE( a != b );
}

TEST_CASE("multipass")
{
  QStringList stringList = qStringListFromStdStringList({"A","B"});
  QStringListUnicodeConstIterator a( stringList.cbegin() );
  QStringListUnicodeConstIterator b(a);

  REQUIRE( a == b );
  REQUIRE( unicodeStringViewEqualsStdString( *a, "A" ) );
  REQUIRE( unicodeStringViewEqualsStdString( *b, "A" ) );

  ++b;
  REQUIRE( a != b );
  REQUIRE( unicodeStringViewEqualsStdString( *a, "A" ) );
  REQUIRE( unicodeStringViewEqualsStdString( *b, "B" ) );
}

/*
 * Tests for LegacyBidirectionalIterator requirements
 */

TEST_CASE("decrement")
{
  QStringList stringList;

  SECTION("AB|CD|E")
  {
    stringList = qStringListFromStdStringList({"AB","CD","E"});
    QStringListUnicodeConstIterator it( stringList.cbegin() );

    ++it;
    ++it;
    REQUIRE( unicodeStringViewEqualsStdString( *it, "E" ) );

    --it;
    REQUIRE( unicodeStringViewEqualsStdString( *it, "CD" ) );

    it--;
    REQUIRE( unicodeStringViewEqualsStdString( *it, "AB" ) );
  }
}
