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
#include "Mdt/PlainText/BoostSpiritQStringConstIterator.h"
#include <QLatin1String>
#include <QLatin1Char>
#include <type_traits>
#include <iterator>

using Mdt::PlainText::BoostSpiritQStringConstIterator;

bool iteratorValueEqualsToLatin1Char(const BoostSpiritQStringConstIterator & it, char c)
{
  return *it == QLatin1Char(c);
}

/*
 * Tests for LegacyIterator requirements
 */

static_assert( std::is_copy_constructible<BoostSpiritQStringConstIterator>::value , "" );
static_assert( std::is_copy_assignable<BoostSpiritQStringConstIterator>::value , "" );
static_assert( std::is_destructible<BoostSpiritQStringConstIterator>::value , "" );

TEST_CASE("copy_construct")
{
  const QString str = QLatin1String("ABCD");
  BoostSpiritQStringConstIterator a( str.cbegin() );
  REQUIRE( iteratorValueEqualsToLatin1Char(a, 'A') );

  BoostSpiritQStringConstIterator b(a);
  REQUIRE( iteratorValueEqualsToLatin1Char(b, 'A') );
}

TEST_CASE("assign")
{
  const QString str = QLatin1String("ABCD");
  BoostSpiritQStringConstIterator a, b;

  a = str.cbegin();
  REQUIRE( iteratorValueEqualsToLatin1Char(a, 'A') );
  b = a;
  REQUIRE( iteratorValueEqualsToLatin1Char(b, 'A') );
}

TEST_CASE("dereference")
{
  const QString str = QLatin1String("ABCD");
  BoostSpiritQStringConstIterator it( str.cbegin() );

  REQUIRE( iteratorValueEqualsToLatin1Char(it, 'A') );
}

TEST_CASE("pre-increment")
{
  const QString str = QLatin1String("ABCD");
  BoostSpiritQStringConstIterator it( str.cbegin() );

  ++it;
  REQUIRE( iteratorValueEqualsToLatin1Char(it, 'B') );
}

/*
 * Tests for LegacyInputIterator requirements
 */

TEST_CASE("comparison")
{
  const QString str = QLatin1String("ABCD");
  BoostSpiritQStringConstIterator a( str.cbegin() );
  auto b = a;

  REQUIRE( a == b );
  REQUIRE( !(a != b) );
}

TEST_CASE("post-increment")
{
  const QString str = QLatin1String("ABCD");
  BoostSpiritQStringConstIterator it( str.cbegin() );

  it++;
  REQUIRE( iteratorValueEqualsToLatin1Char(it, 'B') );
}

/*
 * Tests for LegacyForwardIterator requirements
 */

static_assert( std::is_default_constructible<BoostSpiritQStringConstIterator>::value , "" );

TEST_CASE("multipass")
{
  const QString str = QLatin1String("ABCD");
  BoostSpiritQStringConstIterator a( str.cbegin() );
  auto b = a;

  REQUIRE( a == b );
  REQUIRE( iteratorValueEqualsToLatin1Char(a, 'A') );
  REQUIRE( iteratorValueEqualsToLatin1Char(b, 'A') );

  ++b;
  REQUIRE( a != b );
  REQUIRE( iteratorValueEqualsToLatin1Char(a, 'A') );
  REQUIRE( iteratorValueEqualsToLatin1Char(b, 'B') );
}

/*
 * Tests for LegacyBidirectionalIterator requirements
 */

TEST_CASE("decrement")
{
  const QString str = QLatin1String("ABCD");
  BoostSpiritQStringConstIterator it( str.cbegin() );

  ++it;
  ++it;
  REQUIRE( iteratorValueEqualsToLatin1Char(it, 'C') );

  --it;
  REQUIRE( iteratorValueEqualsToLatin1Char(it, 'B') );
  it--;
  REQUIRE( iteratorValueEqualsToLatin1Char(it, 'A') );
}

/*
 * Tests for LegacyRandomAccessIterator requirements
 */

TEST_CASE("distance")
{
  const QString str = QLatin1String("ABCD");
  BoostSpiritQStringConstIterator it( str.cbegin() );

  REQUIRE( iteratorValueEqualsToLatin1Char(it, 'A') );
  REQUIRE( iteratorValueEqualsToLatin1Char(it + 2, 'C') );
  REQUIRE( iteratorValueEqualsToLatin1Char(2 + it, 'C') );

  auto & r = it;

  r += 3;
  REQUIRE( iteratorValueEqualsToLatin1Char(r, 'D') );

  r -= 2;
  REQUIRE( iteratorValueEqualsToLatin1Char(r, 'B') );

  --r;
  REQUIRE( iteratorValueEqualsToLatin1Char(it, 'A') );

  REQUIRE( it[2] == QLatin1Char('C') );

  auto a = it;
  auto b = it + 2;
  REQUIRE( (b - a) == 2 );
}

TEST_CASE("lt_gt_comparison")
{
  const QString str = QLatin1String("ABCD");
  BoostSpiritQStringConstIterator a( str.cbegin() );
  auto b = a + 1;

  REQUIRE( a < b );
  REQUIRE( a <= b );

  REQUIRE( b > a );
  REQUIRE( b >= a );
}

/*
 * Tests with some STL functions
 */

TEST_CASE("std_copy")
{
  QString destination;
  BoostSpiritQStringConstIterator first;
  BoostSpiritQStringConstIterator last;

  SECTION("abcd")
  {
    const QString source = QLatin1String("abcd");
    first = source.cbegin();
    last = source.cend();
    std::copy( first, last, std::back_inserter(destination) );
    REQUIRE( destination == source );
  }

  SECTION("éöàäèü$£")
  {
    const QString source = QString::fromUtf8("éöàäèü$£");
    first = source.cbegin();
    last = source.cend();
    std::copy( first, last, std::back_inserter(destination) );
    REQUIRE( destination == source );
  }
}

/*
 * Tests with some Sprit parsers
 */

