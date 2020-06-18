/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "catch2/catch.hpp"
#include "Mdt/PlainText/BoostSpiritQStringEncoding.h"
#include "Mdt/PlainText/BoostSpiritQStringContainer.h"
#include <boost/spirit/include/qi.hpp>
#include <QString>
#include <QLatin1String>
// #include <string>

template<typename Grammar>
bool parse(const QString & source, const Grammar & grammar, QString & destination)
{
  return boost::spirit::qi::parse(source.cbegin(), source.cend(), grammar, destination);
}

template<typename Grammar>
bool parse(const QString & source, const Grammar & grammar, QChar & destination)
{
  return boost::spirit::qi::parse(source.cbegin(), source.cend(), grammar, destination);
}


TEST_CASE("char_")
{
  using boost::spirit::qchar::char_;

  QChar result;

  REQUIRE( parse( QLatin1String("A"), char_, result ) );
  REQUIRE( result == QLatin1Char('A') );
}

TEST_CASE("*char_")
{
  using boost::spirit::qchar::char_;

  QString result;

  REQUIRE( parse( QLatin1String("A"), *char_, result ) );
  REQUIRE( result == QLatin1String("A") );
}
