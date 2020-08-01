/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "CsvKarmaGrammarTestCommon.h"

TEST_CASE("ProtectedField")
{
  std::string result;
  CsvGeneratorSettings csvSettings;

  SECTION("A")
  {
    result = generateProtectedField("A", csvSettings);
    REQUIRE( result == "\"A\"" );
  }

  SECTION("AB")
  {
    result = generateProtectedField("AB", csvSettings);
    REQUIRE( result == "\"AB\"" );
  }

  SECTION("ABC")
  {
    result = generateProtectedField("ABC", csvSettings);
    REQUIRE( result == "\"ABC\"" );
  }

  SECTION("ABCD")
  {
    result = generateProtectedField("ABCD", csvSettings);
    REQUIRE( result == "\"ABCD\"" );
  }

  SECTION("1")
  {
    result = generateProtectedField("1", csvSettings);
    REQUIRE( result == "\"1\"" );
  }

  SECTION("1234")
  {
    result = generateProtectedField("1234", csvSettings);
    REQUIRE( result == "\"1234\"" );
  }

  SECTION("\\n")
  {
    result = generateProtectedField("\n", csvSettings);
    REQUIRE( result == "\"\n\"" );
  }

  SECTION("\\r")
  {
    result = generateProtectedField("\r", csvSettings);
    REQUIRE( result == "\"\r\"" );
  }

  SECTION("\\r\\n")
  {
    result = generateProtectedField("\r\n", csvSettings);
    REQUIRE( result == "\"\r\n\"" );
  }

  SECTION("\"A\"")
  {
    result = generateProtectedField("\"A\"", csvSettings);
    REQUIRE( result == "\"\"\"A\"\"\"" );
  }

  SECTION("A\"BC\"D")
  {
    result = generateProtectedField("A\"BC\"D", csvSettings);
    REQUIRE( result == "\"A\"\"BC\"\"D\"" );
  }
}

TEST_CASE("ProtectedField_EXP")
{
  std::string result;
  CsvGeneratorSettings csvSettings;

  SECTION("Add EXP")
  {
    csvSettings.setAddExp(true);

    SECTION("A")
    {
      result = generateProtectedField("A", csvSettings);
      REQUIRE( result == "\"~A\"" );
    }

    SECTION("~A")
    {
      result = generateProtectedField("~A", csvSettings);
      REQUIRE( result == "\"~~A\"" );
    }

    SECTION("A~")
    {
      result = generateProtectedField("A~", csvSettings);
      REQUIRE( result == "\"~A~\"" );
    }
  }

  SECTION("Do not add EXP")
  {
    csvSettings.setAddExp(false);

    SECTION("A")
    {
      result = generateProtectedField("A", csvSettings);
      REQUIRE( result == "\"A\"" );
    }

    SECTION("~A")
    {
      result = generateProtectedField("~A", csvSettings);
      REQUIRE( result == "\"~A\"" );
    }

    SECTION("A~")
    {
      result = generateProtectedField("A~", csvSettings);
      REQUIRE( result == "\"A~\"" );
    }
  }
}

TEST_CASE("CsvFileLine")
{
  std::string result;
  StringRecord record;
  CsvGeneratorSettings csvSettings;

  SECTION("A")
  {
    record = {"A"};
    result = generateCsvFileLineString(record, csvSettings);
    REQUIRE( result == "A" );
  }

  SECTION("A,B")
  {
    record = {"A","B"};
    result = generateCsvFileLineString(record, csvSettings);
    REQUIRE( result == "A,B" );
  }

  REQUIRE(false);
}
