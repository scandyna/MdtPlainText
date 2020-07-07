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
   * Single char CSV - No EOL (No EOL is allowed by RFC 4180)
   */
  SECTION("A")
  {
    record = parseRecord("A", csvSettings);
    REQUIRE( record == StringRecord{"A"} );
  }

  SECTION("A\\n")
  {
    record = parseRecord("A\n", csvSettings);
    REQUIRE( record == StringRecord{"A"} );
  }

  SECTION("A\\r\\n")
  {
    record = parseRecord("A\r\n", csvSettings);
    REQUIRE( record == StringRecord{"A"} );
  }

  SECTION("AB")
  {
    record = parseRecord("AB", csvSettings);
    REQUIRE( record == StringRecord{"AB"} );
  }

  SECTION("A,B")
  {
    record = parseRecord("A,B", csvSettings);
    REQUIRE( record == StringRecord{"A","B"} );
  }

  SECTION("ABC")
  {
    record = parseRecord("ABC", csvSettings);
    REQUIRE( record == StringRecord{"ABC"} );
  }

  SECTION("A,BC")
  {
    record = parseRecord("A,BC", csvSettings);
    REQUIRE( record == StringRecord{"A","BC"} );
  }

  SECTION("AB,C")
  {
    record = parseRecord("AB,C", csvSettings);
    REQUIRE( record == StringRecord{"AB","C"} );
  }

  SECTION("AB,CD")
  {
    record = parseRecord("AB,CD", csvSettings);
    REQUIRE( record == StringRecord{"AB","CD"} );
  }

  SECTION("AB,CD\\n")
  {
    record = parseRecord("AB,CD\n", csvSettings);
    REQUIRE( record == StringRecord{"AB","CD"} );
  }

  SECTION("AB,CD\\r\\n")
  {
    record = parseRecord("AB,CD\r\n", csvSettings);
    REQUIRE( record == StringRecord{"AB","CD"} );
  }

  SECTION("\"AB\",CD")
  {
    record = parseRecord("\"AB\",CD", csvSettings);
    REQUIRE( record == StringRecord{"AB","CD"} );
  }

  SECTION("\"A,B\",CD")
  {
    record = parseRecord("\"A,B\",CD", csvSettings);
    REQUIRE( record == StringRecord{"A,B","CD"} );
  }

  SECTION("\"A\\nB\",CD")
  {
    record = parseRecord("\"A\nB\",CD", csvSettings);
    REQUIRE( record == StringRecord{"A\nB","CD"} );
  }

  SECTION("\"A\\rB\",CD")
  {
    record = parseRecord("\"A\rB\",CD", csvSettings);
    REQUIRE( record == StringRecord{"A\rB","CD"} );
  }

  SECTION("\"A\\n,B\",CD")
  {
    record = parseRecord("\"A\n,B\",CD", csvSettings);
    REQUIRE( record == StringRecord{"A\n,B","CD"} );
  }

  SECTION("A,BC,D,EFG")
  {
    record = parseRecord("A,BC,D,EFG", csvSettings);
    REQUIRE( record == StringRecord{"A","BC","D","EFG"} );
  }

  SECTION("A,BC,D,EFG\\n")
  {
    record = parseRecord("A,BC,D,EFG\n", csvSettings);
    REQUIRE( record == StringRecord{"A","BC","D","EFG"} );
  }
}
