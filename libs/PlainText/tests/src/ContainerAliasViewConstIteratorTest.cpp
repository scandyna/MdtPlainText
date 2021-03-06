/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "catch2/catch.hpp"
#include "Mdt/PlainText/ContainerAliasViewConstIterator.h"
#include <vector>
#include <type_traits>
#include <iterator>
#include <limits>
#include <cmath>
#include <cstdlib>

using Mdt::PlainText::ContainerAliasViewConstIterator;

using IntList = std::vector<int>;
using IntListAsDoubleListIterator = ContainerAliasViewConstIterator<IntList::const_iterator, double>;

static_assert( std::is_same< std::iterator_traits<IntListAsDoubleListIterator>::value_type, const double >::value, "" );
static_assert( std::is_same< std::iterator_traits<IntListAsDoubleListIterator>::iterator_category, std::bidirectional_iterator_tag >::value, "" );


struct AsDoubleStruct
{
  AsDoubleStruct(int i)
   : x(i)
  {
  }

  double x;
};

using IntListAsDoubleStructListIterator = ContainerAliasViewConstIterator<IntList::const_iterator, AsDoubleStruct>;

static_assert( std::is_same< std::iterator_traits<IntListAsDoubleStructListIterator>::value_type, const AsDoubleStruct >::value, "" );
static_assert( std::is_same< std::iterator_traits<IntListAsDoubleStructListIterator>::iterator_category, std::bidirectional_iterator_tag >::value, "" );


bool doubleAreEqual(double a, double b)
{
  return std::abs(a-b) < std::numeric_limits<double>::epsilon();
}


TEST_CASE("construct")
{
  IntList list;

  SECTION("From empty list")
  {
    IntListAsDoubleListIterator first( list.cbegin() );
    IntListAsDoubleListIterator last( list.cend() );
    REQUIRE( first == last );
  }

  SECTION("12")
  {
    list = {12};
    IntListAsDoubleListIterator it( list.cbegin() );
    REQUIRE( *it == 12.0 );
  }
}

/*
 * Tests for LegacyIterator requirements
 */

static_assert( std::is_copy_constructible<IntListAsDoubleListIterator>::value , "" );
static_assert( std::is_copy_assignable<IntListAsDoubleListIterator>::value , "" );
static_assert( std::is_destructible<IntListAsDoubleListIterator>::value , "" );

TEST_CASE("copy_construct")
{
  IntList list;

  SECTION("empty list")
  {
    IntListAsDoubleListIterator a( list.cbegin() );
    IntListAsDoubleListIterator b(a);
    REQUIRE( a == b );
  }

  SECTION("26")
  {
    list = {26};
    IntListAsDoubleListIterator a( list.cbegin() );
    IntListAsDoubleListIterator b(a);
    REQUIRE( doubleAreEqual(*b, 26.0) );
  }
}

TEST_CASE("assign")
{
  IntList list{89};

  IntListAsDoubleListIterator b;

  IntListAsDoubleListIterator a( list.cbegin() );
  REQUIRE( doubleAreEqual(*a, 89.0) );

  b = a;
  REQUIRE( doubleAreEqual(*b, 89.0) );
}

TEST_CASE("dereference")
{
  IntList list{32};
  IntListAsDoubleListIterator it( list.cbegin() );
  REQUIRE( doubleAreEqual(*it, 32.0) );
}

TEST_CASE("pre-increment")
{
  IntList list;

  SECTION("12,24")
  {
    list = {12,24};
    IntListAsDoubleListIterator it( list.cbegin() );
    REQUIRE( doubleAreEqual(*it, 12.0) );

    ++it;
    REQUIRE( doubleAreEqual(*it, 24.0) );
  }
}

/*
 * Tests for LegacyInputIterator requirements
 */

TEST_CASE("comparison")
{
  IntList list{47};
  IntListAsDoubleListIterator a( list.cbegin() );
  IntListAsDoubleListIterator b( list.cbegin() );

  REQUIRE( a == b );
  REQUIRE( !(a != b) );
}

// TEST_CASE("operator ->")
// {
//   IntList list{74};
//   IntListAsDoubleStructListIterator it( list.cbegin() );
//
//   REQUIRE( doubleAreEqual(it->x, 74.0) );
// }

TEST_CASE("post-increment")
{
  IntList list;

  SECTION("24,36")
  {
    list = {24,36};
    IntListAsDoubleListIterator it( list.cbegin() );
    REQUIRE( doubleAreEqual(*it, 24.0) );

    it++;
    REQUIRE( doubleAreEqual(*it, 36.0) );
  }
}

/*
 * Tests for LegacyForwardIterator requirements
 */

static_assert( std::is_default_constructible<IntListAsDoubleListIterator>::value , "" );

TEST_CASE("default_construct")
{
  IntList list{1};
  IntListAsDoubleListIterator a( list.cbegin() );

  IntListAsDoubleListIterator b;
  /*
   * From here: https://en.cppreference.com/w/cpp/named_req/ForwardIterator
   * A value-initialized LegacyForwardIterator behaves like the past-the-end iterator
   * of some unspecified empty container.
   *
   * Comparing it with a iterator to a existing container is undefined.
   * On MSVC, debug build, this fires a assertion
   * (a and b are not from the same container)
   *
   *The only thing we can do is assign a valid one to it.
   */
  //REQUIRE( a != b );

  b = a;
  REQUIRE( a == b );
}

TEST_CASE("multipass")
{
  IntList list{1,2};
  IntListAsDoubleListIterator a( list.cbegin() );
  IntListAsDoubleListIterator b(a);

  REQUIRE( a == b );
  REQUIRE( doubleAreEqual(*a, 1.0) );
  REQUIRE( doubleAreEqual(*b, 1.0) );

  ++b;
  REQUIRE( doubleAreEqual(*a, 1.0) );
  REQUIRE( doubleAreEqual(*b, 2.0) );
}

/*
 * Tests for LegacyBidirectionalIterator requirements
 */

TEST_CASE("decrement")
{
  IntList list;

  SECTION("10,11,12")
  {
    list = {10,11,12};
    IntListAsDoubleListIterator it( list.cbegin() );

    ++it;
    ++it;
    REQUIRE( doubleAreEqual(*it, 12.0) );

    --it;
    REQUIRE( doubleAreEqual(*it, 11.0) );

    it--;
    REQUIRE( doubleAreEqual(*it, 10.0) );
  }
}
