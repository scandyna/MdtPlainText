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
#include "Mdt/PlainText/BoostSpiritQStringIterator.h"
#include "Mdt/PlainText/BoostSpiritQStringConstIterator.h"
#include "Mdt/PlainText/BoostSpiritQStringContainer.h"
#include <boost/spirit/include/qi.hpp>
#include <QLatin1String>
#include <QLatin1Char>

using Mdt::PlainText::BoostSpiritQStringIterator;
using Mdt::PlainText::BoostSpiritQStringConstIterator;

template<typename Iterator>
bool iteratorValueEqualsToLatin1Char(const Iterator & it, char c)
{
  return *it == QLatin1Char(c);
}

/*
 * Tests for LegacyIterator requirements
 */

static_assert( std::is_copy_constructible<BoostSpiritQStringIterator>::value , "" );
static_assert( std::is_copy_assignable<BoostSpiritQStringIterator>::value , "" );
static_assert( std::is_destructible<BoostSpiritQStringIterator>::value , "" );

static_assert( std::is_copy_constructible<BoostSpiritQStringConstIterator>::value , "" );
static_assert( std::is_copy_assignable<BoostSpiritQStringConstIterator>::value , "" );
static_assert( std::is_destructible<BoostSpiritQStringConstIterator>::value , "" );

TEST_CASE("copy_construct_const")
{
  const QString str = QLatin1String("ABCD");
//   BoostSpiritQStringConstIterator a( str.cbegin() );
//   REQUIRE( iteratorValueEqualsToLatin1Char(a, 'A') );

//   BoostSpiritQStringConstIterator b(a);
//   REQUIRE( iteratorValueEqualsToLatin1Char(b, 'A') );
}

TEMPLATE_TEST_CASE("copy_construct","",BoostSpiritQStringIterator,BoostSpiritQStringConstIterator)
{
  using Iterator = TestType;

  QString str = QLatin1String("ABCD");
//   Iterator a( str.begin() );
//   REQUIRE( iteratorValueEqualsToLatin1Char(a, 'A') );
/*
  Iterator b(a);
  REQUIRE( iteratorValueEqualsToLatin1Char(b, 'A') );*/
}

TEST_CASE("assign")
{
  REQUIRE(false);
}

TEST_CASE("dereference_const")
{
  const QString str = QLatin1String("ABCD");
//   BoostSpiritQStringConstIterator it( str.cbegin() );

//   REQUIRE( *it == QLatin1Char('A') );
}

TEMPLATE_TEST_CASE("dereference_read","",BoostSpiritQStringIterator,BoostSpiritQStringConstIterator)
{
  using Iterator = TestType;

  QString str = QLatin1String("ABCD");
//   Iterator it( str.begin() );

//   REQUIRE( *it == QLatin1Char('A') );
}

TEST_CASE("dereference_write")
{
  QString str = QLatin1String("ABCD");
  BoostSpiritQStringIterator it( str.begin() );

  *it = 'F';
  REQUIRE( str == QLatin1String("FBCD") );
}
