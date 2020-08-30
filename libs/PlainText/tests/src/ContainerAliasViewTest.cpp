/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "catch2/catch.hpp"
#include "Mdt/PlainText/ContainerAliasView"
#include <vector>
#include <type_traits>
#include <limits>
#include <cmath>
#include <cstdlib>

using Mdt::PlainText::ContainerAliasView;

using IntList = std::vector<int>;
using IntListAsDoubleListView = ContainerAliasView<IntList, double>;

bool doubleAreEqual(double a, double b)
{
  return std::abs(a-b) < std::numeric_limits<double>::epsilon();
}

static_assert( std::is_copy_constructible<IntListAsDoubleListView>::value , "" );
static_assert( std::is_copy_assignable<IntListAsDoubleListView>::value , "" );
static_assert( std::is_destructible<IntListAsDoubleListView>::value , "" );

TEST_CASE("construct")
{
  IntList list{12};
  IntListAsDoubleListView view(list);
  REQUIRE( view.size() == 1 );
}

TEST_CASE("size")
{
  IntList list;

  SECTION("empty list")
  {
    IntListAsDoubleListView view(list);
    REQUIRE( view.size() == 0 );
  }

  SECTION("1")
  {
    list = {1};
    IntListAsDoubleListView view(list);
    REQUIRE( view.size() == 1 );
  }

  SECTION("1,2")
  {
    list = {1,2};
    IntListAsDoubleListView view(list);
    REQUIRE( view.size() == 2 );
  }
}

TEST_CASE("at")
{
  IntList list;

  SECTION("29")
  {
    list = {29};
    IntListAsDoubleListView view(list);
    REQUIRE( view.size() == 1 );
    REQUIRE( doubleAreEqual( view.at(0), 29.0 ) );
  }
}

// TEST_CASE("operator_square_bracket")
// {
//   REQUIRE(false);
// }

TEST_CASE("iterators")
{
  IntList list;

  SECTION("empty list")
  {
    IntListAsDoubleListView view(list);
    REQUIRE( view.begin() == view.end() );
    REQUIRE( view.cbegin() == view.cend() );
  }

  SECTION("25")
  {
    list = {25};
    IntListAsDoubleListView view(list);

    REQUIRE( view.begin() != view.end() );
    REQUIRE( doubleAreEqual( *view.begin(), 25.0 ) );

    REQUIRE( view.cbegin() != view.cend() );
    REQUIRE( doubleAreEqual( *view.cbegin(), 25.0 ) );
  }
}

TEST_CASE("Range_for")
{
  IntList list = {47};
  IntListAsDoubleListView view(list);

  for(double x : view){
    REQUIRE( doubleAreEqual(x, 47.0) );
  }
}

// TEST_CASE("std_copy")
// {
//   REQUIRE(false);
// }
