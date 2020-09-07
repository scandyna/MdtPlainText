/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "CsvQiGrammarTestCommon.h"

TEST_CASE("SafeChar")
{
  uint32_t result;
  CsvParserSettings csvSettings;

  SECTION("A")
  {
    result = parseSafeChar("A", csvSettings);
    REQUIRE( result == 'A' );
  }

  SECTION(",")
  {
    REQUIRE( parseSafeCharFails(",", csvSettings) );
  }

  SECTION("space")
  {
    REQUIRE( parseSafeCharFails(" ", csvSettings) );
  }
}

TEST_CASE("UnprotectedField")
{
  std::string data;
  CsvParserSettings csvSettings;

  SECTION("empty")
  {
    data = parseUnprotectedField("", csvSettings);
    REQUIRE( data == "" );
  }

  SECTION(",")
  {
    data = parseUnprotectedField(",", csvSettings);
    REQUIRE( data == "" );
  }

  SECTION("A,")
  {
    data = parseUnprotectedField("A,", csvSettings);
    REQUIRE( data == "A" );
  }

  SECTION("AB,")
  {
    data = parseUnprotectedField("AB,", csvSettings);
    REQUIRE( data == "AB" );
  }

  SECTION(",A")
  {
    data = parseUnprotectedField(",A", csvSettings);
    REQUIRE( data == "" );
  }

  SECTION(",AB")
  {
    data = parseUnprotectedField(",AB", csvSettings);
    REQUIRE( data == "" );
  }

  SECTION("A,B")
  {
    data = parseUnprotectedField("A,B", csvSettings);
    REQUIRE( data == "A" );
  }

  SECTION("\"")
  {
    data = parseUnprotectedField("\"", csvSettings);
    REQUIRE( data == "" );
  }

  SECTION("A B")
  {
    data = parseUnprotectedField("A B", csvSettings);
    REQUIRE( data == "A B" );
  }
}

TEST_CASE("NonEmptyUnprotectedField")
{
  std::string data;
  CsvParserSettings csvSettings;

  SECTION("empty")
  {
    REQUIRE( parseNonEmptyUnprotectedFieldFails("", csvSettings) );
  }

  SECTION(",")
  {
    REQUIRE( parseNonEmptyUnprotectedFieldFails(",", csvSettings) );
  }

  SECTION("A,")
  {
    data = parseNonEmptyUnprotectedField("A,", csvSettings);
    REQUIRE( data == "A" );
  }

  SECTION("AB,")
  {
    data = parseNonEmptyUnprotectedField("AB,", csvSettings);
    REQUIRE( data == "AB" );
  }

  SECTION(",A")
  {
    REQUIRE( parseNonEmptyUnprotectedFieldFails(",A", csvSettings) );
  }

  SECTION(",AB")
  {
    REQUIRE( parseNonEmptyUnprotectedFieldFails(",AB", csvSettings) );
  }

  SECTION("A,B")
  {
    data = parseNonEmptyUnprotectedField("A,B", csvSettings);
    REQUIRE( data == "A" );
  }

  SECTION("\"")
  {
    REQUIRE( parseNonEmptyUnprotectedFieldFails("\"", csvSettings) );
  }

  SECTION("A B")
  {
    data = parseNonEmptyUnprotectedField("A B", csvSettings);
    REQUIRE( data == "A B" );
  }
}

TEST_CASE("UnprotectedField_NonEmptyUnprotectedField")
{
  CsvParserSettings csvSettings;

  const auto data = GENERATE( values<InputExpectedStringData>
    ({
      {"A","A"},
      {"AB","AB"},
      {"ABC","ABC"},
      {"ABCD","ABCD"},
      {"A B","A B"},
      {"A B  C","A B  C"},
    })
  );

  SECTION("UnprotectedField")
  {
    REQUIRE( parseUnprotectedField(data.input, csvSettings) == data.expected );
  }

  SECTION("NonEmptyUnprotectedField")
  {
    REQUIRE( parseNonEmptyUnprotectedField(data.input, csvSettings) == data.expected );
  }
}

TEST_CASE("UnprotectedField_EXP")
{
  std::string data;
  CsvParserSettings csvSettings;

  SECTION("Parse EXP")
  {
    SECTION("~")
    {
      data = parseUnprotectedField("~", csvSettings);
      REQUIRE( data == "" );
    }
  }

  SECTION("Ignore EXP")
  {
    csvSettings.setParseExp(false);

    SECTION("~")
    {
      data = parseUnprotectedField("~", csvSettings);
      REQUIRE( data == "~" );
    }
  }
}

TEST_CASE("NonEmptyUnprotectedField_EXP")
{
  std::string data;
  CsvParserSettings csvSettings;

  SECTION("Parse EXP")
  {
    SECTION("~")
    {
      REQUIRE( parseNonEmptyUnprotectedFieldFails("~", csvSettings) );
    }
  }

  SECTION("Ignore EXP")
  {
    csvSettings.setParseExp(false);

    SECTION("~")
    {
      data = parseNonEmptyUnprotectedField("~", csvSettings);
      REQUIRE( data == "~" );
    }
  }
}

TEST_CASE("UnprotectedField_NonEmptyUnprotectedField_EXP")
{
  CsvParserSettings csvSettings;

  SECTION("Parse EXP")
  {
    const auto data = GENERATE( values<InputExpectedStringData>
      ({
        {"~A","A"},
        {"~AB","AB"},
        {"~A~","A~"},
        {"~AB~","AB~"}
      })
    );

    SECTION("UnprotectedField")
    {
      REQUIRE( parseUnprotectedField(data.input, csvSettings) == data.expected );
    }

    SECTION("NonEmptyUnprotectedField")
    {
      REQUIRE( parseNonEmptyUnprotectedField(data.input, csvSettings) == data.expected );
    }
  }

  SECTION("Ignore EXP")
  {
    csvSettings.setParseExp(false);

    const auto data = GENERATE( values<InputExpectedStringData>
      ({
        {"A","A"},
        {"AB","AB"},
        {"ABC","ABC"},
        {"ABCD","ABCD"},
        {"~A","~A"},
        {"~AB","~AB"},
        {"~A~","~A~"},
        {"~AB~","~AB~"}
      })
    );

    SECTION("UnprotectedField")
    {
      REQUIRE( parseUnprotectedField(data.input, csvSettings) == data.expected );
    }

    SECTION("NonEmptyUnprotectedField")
    {
      REQUIRE( parseNonEmptyUnprotectedField(data.input, csvSettings) == data.expected );
    }
  }
}

TEST_CASE("ProtectedField")
{
  CsvParserSettings csvSettings;

  SECTION("Non quoted string fails")
  {
    const auto nonQuotedData = GENERATE( as<std::string>(), "","A","AB","ABC" );

    SECTION("Parse EXP")
    {
      REQUIRE( parseProtectedFieldFails(nonQuotedData, csvSettings) );
    }

    SECTION("Ignore EXP")
    {
      csvSettings.setParseExp(false);

      REQUIRE( parseProtectedFieldFails(nonQuotedData, csvSettings) );
    }
  }

  SECTION("Quoted string")
  {
    const auto data = GENERATE( values<InputExpectedStringData>
      ({
        {"\"A\"","A"},
        {"\"AB\"","AB"},
        {"\"ABC\"","ABC"},
        {"\"ABCD\"","ABCD"},
        {"\"A\"\"B\"","A\"B"},
        {"\"A\"\"BC\"\"D\"","A\"BC\"D"},
        {"\"A \"","A "},
        {"\" A\""," A"},
        {"\" A \""," A "},
        {"\"AB \"","AB "},
        {"\"A B\"","A B"},
        {"\" AB\""," AB"},
        {"\" AB \""," AB "},
        {"\" A B \""," A B "},
        {"\"A\nB\"","A\nB"},
        {"\"AB\nC\"","AB\nC"},
        {"\"A\nBC\"","A\nBC"},
        {"\"AB\rC\"","AB\rC"},
        {"\"A\r\nB\"","A\r\nB"},
        {"\"AB\r\nC\"","AB\r\nC"},
        {"\"A\r\nBC\"","A\r\nBC"},
        {"\"A,B\"","A,B"},
        {"\"A,BC\"","A,BC"},
        {"\"AB,C\"","AB,C"}
      })
    );

    SECTION("Parse EXP")
    {
      REQUIRE( parseProtectedField(data.input, csvSettings) == data.expected );
    }

    SECTION("Ignore EXP")
    {
      csvSettings.setParseExp(false);

      REQUIRE( parseProtectedField(data.input, csvSettings) == data.expected );
    }
  }
}

TEST_CASE("ProtectedField_EXP")
{
  std::string data;
  CsvParserSettings csvSettings;

  SECTION("Parse EXP")
  {
    SECTION("~")
    {
      REQUIRE( parseProtectedField("\"~\"", csvSettings) == "" );
    }

    SECTION("~A")
    {
      REQUIRE( parseProtectedField("\"~A\"", csvSettings) == "A" );
    }

    SECTION("~AB")
    {
      REQUIRE( parseProtectedField("\"~AB\"", csvSettings) == "AB" );
    }

    SECTION("~A~")
    {
      REQUIRE( parseProtectedField("\"~A~\"", csvSettings) == "A~" );
    }

    SECTION("~AB~")
    {
      REQUIRE( parseProtectedField("\"~AB~\"", csvSettings) == "AB~" );
    }
  }

  SECTION("Ignore EXP")
  {
    csvSettings.setParseExp(false);

    SECTION("~")
    {
      REQUIRE( parseProtectedField("\"~\"", csvSettings) == "~" );
    }

    SECTION("~A")
    {
      REQUIRE( parseProtectedField("\"~A\"", csvSettings) == "~A" );
    }

    SECTION("~AB")
    {
      REQUIRE( parseProtectedField("\"~AB\"", csvSettings) == "~AB" );
    }

    SECTION("~A~")
    {
      REQUIRE( parseProtectedField("\"~A~\"", csvSettings) == "~A~" );
    }

    SECTION("~AB~")
    {
      REQUIRE( parseProtectedField("\"~AB~\"", csvSettings) == "~AB~" );
    }
  }
}

TEST_CASE("FieldColumn")
{
  CsvParserSettings csvSettings;

  SECTION("Unquoted empty")
  {
    REQUIRE( parseFieldColumn("", csvSettings) == "" );
  }

  SECTION("Quoted empty")
  {
    REQUIRE( parseFieldColumn("\"\"", csvSettings) == "" );
  }
}

TEST_CASE("NonEmptyFieldColumn")
{
  CsvParserSettings csvSettings;

  SECTION("Unquoted empty")
  {
    REQUIRE( parseNonEmptyFieldColumnFails("", csvSettings) );
  }

  SECTION("Quoted empty")
  {
    REQUIRE( parseNonEmptyFieldColumn("\"\"", csvSettings) == "" );
  }
}

TEST_CASE("FieldColumn_NonEmptyFieldColumn")
{
  CsvParserSettings csvSettings;

  const auto data = GENERATE( values<InputExpectedStringData>
    ({
      {"A","A"},
      {"\"A\"","A"},
      {"ABCD","ABCD"},
      {"\"ABCD\"","ABCD"}
    })
  );

  SECTION("FieldColumn")
  {
    REQUIRE( parseFieldColumn(data.input, csvSettings) == data.expected );
  }

  SECTION("NonEmptyFieldColumn")
  {
    REQUIRE( parseNonEmptyFieldColumn(data.input, csvSettings) == data.expected );
  }
}

TEST_CASE("CsvRecord")
{
  StringRecord record;
  CsvParserSettings csvSettings;

  SECTION("empty")
  {
    REQUIRE( parseCsvRecordFails("", csvSettings) );
  }

  /*
   * Single char CSV - No EOL (No EOL is allowed by RFC 4180)
   */
  SECTION("A")
  {
    record = parseCsvRecord("A", csvSettings);
    REQUIRE( record == StringRecord{"A"} );
  }

  SECTION("A\\n")
  {
    record = parseCsvRecord("A\n", csvSettings);
    REQUIRE( record == StringRecord{"A"} );
  }

  SECTION("A\\r\\n")
  {
    record = parseCsvRecord("A\r\n", csvSettings);
    REQUIRE( record == StringRecord{"A"} );
  }

  SECTION("AB")
  {
    record = parseCsvRecord("AB", csvSettings);
    REQUIRE( record == StringRecord{"AB"} );
  }

  SECTION("A,B")
  {
    record = parseCsvRecord("A,B", csvSettings);
    REQUIRE( record == StringRecord{"A","B"} );
  }

  SECTION(",B")
  {
    record = parseCsvRecord(",B", csvSettings);
    REQUIRE( record == StringRecord{"","B"} );
  }

  SECTION("A,")
  {
    record = parseCsvRecord("A,", csvSettings);
    REQUIRE( record == StringRecord{"A",""} );
  }

  SECTION("A,\\n")
  {
    record = parseCsvRecord("A,\n", csvSettings);
    REQUIRE( record == StringRecord{"A",""} );
  }

  SECTION("AB,")
  {
    record = parseCsvRecord("AB,", csvSettings);
    REQUIRE( record == StringRecord{"AB",""} );
  }

  SECTION("ABC")
  {
    record = parseCsvRecord("ABC", csvSettings);
    REQUIRE( record == StringRecord{"ABC"} );
  }

  SECTION("A,BC")
  {
    record = parseCsvRecord("A,BC", csvSettings);
    REQUIRE( record == StringRecord{"A","BC"} );
  }

  SECTION("AB,C")
  {
    record = parseCsvRecord("AB,C", csvSettings);
    REQUIRE( record == StringRecord{"AB","C"} );
  }

  SECTION("AB,CD")
  {
    record = parseCsvRecord("AB,CD", csvSettings);
    REQUIRE( record == StringRecord{"AB","CD"} );
  }

  SECTION("AB,CD\\n")
  {
    record = parseCsvRecord("AB,CD\n", csvSettings);
    REQUIRE( record == StringRecord{"AB","CD"} );
  }

  SECTION("AB,CD\\r\\n")
  {
    record = parseCsvRecord("AB,CD\r\n", csvSettings);
    REQUIRE( record == StringRecord{"AB","CD"} );
  }

  SECTION("\"AB\",CD")
  {
    record = parseCsvRecord("\"AB\",CD", csvSettings);
    REQUIRE( record == StringRecord{"AB","CD"} );
  }

  SECTION("\"A,B\",CD")
  {
    record = parseCsvRecord("\"A,B\",CD", csvSettings);
    REQUIRE( record == StringRecord{"A,B","CD"} );
  }

  SECTION("\"A\\nB\",CD")
  {
    record = parseCsvRecord("\"A\nB\",CD", csvSettings);
    REQUIRE( record == StringRecord{"A\nB","CD"} );
  }

  SECTION("\"A\\rB\",CD")
  {
    record = parseCsvRecord("\"A\rB\",CD", csvSettings);
    REQUIRE( record == StringRecord{"A\rB","CD"} );
  }

  SECTION("\"A\\n,B\",CD")
  {
    record = parseCsvRecord("\"A\n,B\",CD", csvSettings);
    REQUIRE( record == StringRecord{"A\n,B","CD"} );
  }

  SECTION("A,BC,D,EFG")
  {
    record = parseCsvRecord("A,BC,D,EFG", csvSettings);
    REQUIRE( record == StringRecord{"A","BC","D","EFG"} );
  }

  SECTION("A,BC,D,EFG\\n")
  {
    record = parseCsvRecord("A,BC,D,EFG\n", csvSettings);
    REQUIRE( record == StringRecord{"A","BC","D","EFG"} );
  }

  SECTION("A B")
  {
    record = parseCsvRecord("A B", csvSettings);
    REQUIRE( record == StringRecord{"A B"} );
  }

  SECTION("A  B")
  {
    record = parseCsvRecord("A  B", csvSettings);
    REQUIRE( record == StringRecord{"A  B"} );
  }

  SECTION("A B,C")
  {
    record = parseCsvRecord("A B,C", csvSettings);
    REQUIRE( record == StringRecord{"A B", "C"} );
  }
}

TEST_CASE("CsvFileLine")
{
  StringRecord record;
  CsvParserSettings csvSettings;

  SECTION("empty")
  {
    REQUIRE( parseCsvFileLineStringFails("", csvSettings) );
  }

  SECTION("A")
  {
    record = parseCsvFileLineString("A", csvSettings);
    REQUIRE( record == StringRecord{"A"} );
  }

  SECTION("A\\n")
  {
    record = parseCsvFileLineString("A\n", csvSettings);
    REQUIRE( record == StringRecord{"A"} );
  }

  SECTION("A,BC,D,EFG")
  {
    record = parseCsvFileLineString("A,BC,D,EFG", csvSettings);
    REQUIRE( record == StringRecord{"A","BC","D","EFG"} );
  }

  SECTION("A,BC,D,EFG\\n")
  {
    record = parseCsvFileLineString("A,BC,D,EFG\n", csvSettings);
    REQUIRE( record == StringRecord{"A","BC","D","EFG"} );
  }
}

TEST_CASE("CsvFile")
{
  StringTable table;
  CsvParserSettings csvSettings;

  SECTION("empty")
  {
    REQUIRE( parseCsvFileStringFails("", csvSettings) );
  }

  SECTION("A")
  {
    table = parseCsvFileString("A", csvSettings);
    REQUIRE( table == StringTable{{"A"}} );
  }

  SECTION("A,BC\\n")
  {
    table = parseCsvFileString("A,BC\n", csvSettings);
    REQUIRE( table == StringTable{{"A","BC"}} );
  }

  SECTION("A\\nB")
  {
    table = parseCsvFileString("A\nB", csvSettings);
    REQUIRE( table == StringTable{{"A"},{"B"}} );
  }

  SECTION("A\\nB\\n")
  {
    table = parseCsvFileString("A\nB\n", csvSettings);
    REQUIRE( table == StringTable{{"A"},{"B"}} );
  }
}
