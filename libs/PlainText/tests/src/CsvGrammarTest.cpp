/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "CsvGrammarTestCommon.h"

TEST_CASE("FieldColumnRule")
{
  std::string data;
  CsvParserSettings csvSettings;

  SECTION("empty")
  {
    data = parseFieldColumn("", csvSettings);
    REQUIRE( data == "" );
  }

  SECTION("A")
  {
    data = parseFieldColumn("A", csvSettings);
    REQUIRE( data == "A" );
  }

  SECTION("\"A\"")
  {
    data = parseFieldColumn("\"A\"", csvSettings);
    REQUIRE( data == "A" );
  }

  SECTION("AB")
  {
    data = parseFieldColumn("AB", csvSettings);
    REQUIRE( data == "AB" );
  }

  SECTION("ABC")
  {
    data = parseFieldColumn("ABC", csvSettings);
    REQUIRE( data == "ABC" );
  }

  SECTION("ABCD")
  {
    data = parseFieldColumn("ABCD", csvSettings);
    REQUIRE( data == "ABCD" );
  }

  SECTION("\"ABCD\"")
  {
    data = parseFieldColumn("\"ABCD\"", csvSettings);
    REQUIRE( data == "ABCD" );
  }

  SECTION("\"A\"\"B\"")
  {
    data = parseFieldColumn("\"A\"\"B\"", csvSettings);
    REQUIRE( data == "A\"B" );
  }

  SECTION("\"A\"\"BC\"\"D\"")
  {
    data = parseFieldColumn("\"A\"\"BC\"\"D\"", csvSettings);
    REQUIRE( data == "A\"BC\"D" );
  }

  SECTION("\"A \"")
  {
    data = parseFieldColumn("\"A \"", csvSettings);
    REQUIRE( data == "A " );
  }

  SECTION("\"AB \"")
  {
    data = parseFieldColumn("\"AB \"", csvSettings);
    REQUIRE( data == "AB " );
  }

  SECTION("\"A B\"")
  {
    data = parseFieldColumn("\"A B\"", csvSettings);
    REQUIRE( data == "A B" );
  }

  SECTION("\" AB \"")
  {
    data = parseFieldColumn("\" AB \"", csvSettings);
    REQUIRE( data == " AB " );
  }

  SECTION("\"A,B\"")
  {
    data = parseFieldColumn("\"A,B\"", csvSettings);
    REQUIRE( data == "A,B" );
  }

  SECTION("\"A\\nB\"")
  {
    data = parseFieldColumn("\"A\nB\"", csvSettings);
    REQUIRE( data == "A\nB" );
  }

  SECTION("\"A\\rB\"")
  {
    data = parseFieldColumn("\"A\rB\"", csvSettings);
    REQUIRE( data == "A\rB" );
  }

  SECTION("\"A\\r\\nB\"")
  {
    data = parseFieldColumn("\"A\r\nB\"", csvSettings);
    REQUIRE( data == "A\r\nB" );
  }
}

TEST_CASE("FieldColumnRule Excel protection marker")
{
  std::string data;
  CsvParserSettings csvSettings;

  SECTION("A (EXP ON)")
  {
    csvSettings.setParseExp(true);
    data = parseFieldColumn("A", csvSettings);
    REQUIRE( data == "A" );
  }

  SECTION("~A (EXP ON)")
  {
    csvSettings.setParseExp(true);
    data = parseFieldColumn("~A", csvSettings);
    REQUIRE( data == "A" );
  }

  SECTION("~ABCD (EXP ON)")
  {
    csvSettings.setParseExp(true);
    data = parseFieldColumn("~ABCD", csvSettings);
    REQUIRE( data == "ABCD" );
  }

  SECTION("~A (EXP OFF)")
  {
    csvSettings.setParseExp(false);
    data = parseFieldColumn("~A", csvSettings);
    REQUIRE( data == "~A" );
  }

  SECTION("~ABCD (EXP OFF)")
  {
    csvSettings.setParseExp(false);
    data = parseFieldColumn("~ABCD", csvSettings);
    REQUIRE( data == "~ABCD" );
  }

}

TEST_CASE("RecordRule")
{
  StringRecord record;
  CsvParserSettings csvSettings;

  /*
   * Empty CSV source
   * Parser should simply return a empty result.
   * (the user of the library can then choose to simply display/process nothing,
   *  or warn the user of his application about empty source)
   */
  SECTION("Empty")
  {
    record = parseRecord("", csvSettings);
    REQUIRE( record.size() == 0 );
  }

  /*
   * Single char CSV - No EOL (No EOL is allowed by RFC 4180)
   */
  SECTION("A")
  {
    record = parseRecord("A", csvSettings);
    REQUIRE( record == StringRecord{"A"} );
  }
}
