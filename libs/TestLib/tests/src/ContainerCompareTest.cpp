/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "catch2/catch.hpp"
#include "Mdt/PlainText/TestLib/ContainerCompare.h"
#include <QLatin1String>

using namespace Mdt::PlainText::TestLib;

TEST_CASE("containerSize")
{
  SECTION("record_std_string")
  {
    std::vector<std::string> record{"AB","C"};
    REQUIRE( containerSize(record) == 2 );
  }

  SECTION("record_QString")
  {
    std::vector<QString> record{QLatin1String("AB"),QLatin1String("C")};
    REQUIRE( containerSize(record) == 2 );
  }
}

TEST_CASE("stringMatches")
{
  SECTION("std_string")
  {
    const std::string s = "A";
    REQUIRE( stringMatches(s, "A") );
    REQUIRE( !stringMatches(s, "B") );
  }

  SECTION("QString")
  {
    const QString s = QLatin1String("A");
    REQUIRE( stringMatches(s, "A") );
    REQUIRE( !stringMatches(s, "B") );
  }
}

TEST_CASE("recordMatches")
{
  SECTION("record_std_string")
  {
    const std::vector<std::string> record{"A","B","C"};
    REQUIRE( recordMatches(record, {"A","B","C"}) );
    REQUIRE( !recordMatches(record, {"A","B","E"}) );
    REQUIRE( !recordMatches(record, {"A","B"}) );
    REQUIRE( !recordMatches(record, {"A","B","C","D"}) );
  }

  SECTION("record_QString")
  {
    const std::vector<QString> record{QLatin1String("A"),QLatin1String("B"),QLatin1String("C")};
    REQUIRE( recordMatches(record, {"A","B","C"}) );
    REQUIRE( !recordMatches(record, {"A","B","E"}) );
    REQUIRE( !recordMatches(record, {"A","B"}) );
    REQUIRE( !recordMatches(record, {"A","B","C","D"}) );
  }
}

TEST_CASE("tableMatches")
{
  const std::vector< std::vector<std::string> > referenceTable{
    {"A","B","C"},
    {"1","2","3"}
  };

  SECTION("std_string (A,B,C)(1,2,3)")
  {
    const std::vector< std::vector<std::string> > table{
      {"A","B","C"},
      {"1","2","3"}
    };
    REQUIRE( tableMatches(table, referenceTable) );
  }

  SECTION("std_string (A,B,C)(1,2,4)")
  {
    const std::vector< std::vector<std::string> > table{
      {"A","B","C"},
      {"1","2","4"}
    };
    REQUIRE( !tableMatches(table, referenceTable) );
  }

  SECTION("std_string (A,B,C)(1,2)")
  {
    const std::vector< std::vector<std::string> > table{
      {"A","B","C"},
      {"1","2"}
    };
    REQUIRE( !tableMatches(table, referenceTable) );
  }

  SECTION("std_string (A,B,C)")
  {
    const std::vector< std::vector<std::string> > table{
      {"A","B","C"}
    };
    REQUIRE( !tableMatches(table, referenceTable) );
  }

}
