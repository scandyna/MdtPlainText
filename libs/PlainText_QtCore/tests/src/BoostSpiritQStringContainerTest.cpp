/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "catch2/catch.hpp"
#include "Mdt/PlainText/BoostSpiritQStringContainer.h"
#include <boost/spirit/include/qi.hpp>
#include <QString>
#include <QLatin1String>
#include <string>

template<typename Grammar>
bool parse(const std::string & source, const Grammar & grammar, QString & destination)
{
  return boost::spirit::qi::parse(source.cbegin(), source.cend(), grammar, destination);
}

TEST_CASE("from_std_string")
{
  using boost::spirit::standard::char_;

  QString result;

  SECTION("A")
  {
    REQUIRE( parse("A", *char_, result) );
    REQUIRE( result == QLatin1String("A") );
  }

  SECTION("AB")
  {
    REQUIRE( parse("AB", *char_, result) );
    REQUIRE( result == QLatin1String("AB") );
  }

  SECTION("ABC")
  {
    REQUIRE( parse("ABC", *char_, result) );
    REQUIRE( result == QLatin1String("ABC") );
  }
}


TEST_CASE("from_std_wstring")
{
  REQUIRE( false );
}
