/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "CsvKarmaGrammarTestCommon.h"

TEST_CASE("SafeChar")
{
  std::string result;
  CsvGeneratorSettings csvSettings;

  SECTION("A")
  {
    result = generateSafeChar('A', csvSettings);
    REQUIRE( result == "A" );
  }

  SECTION(",")
  {
    REQUIRE( generateSafeCharFails(',', csvSettings) );
  }

  SECTION("space")
  {
    REQUIRE( generateSafeCharFails(' ', csvSettings) );
  }
}

TEST_CASE("UnprotectedField")
{
  std::string result;
  CsvGeneratorSettings csvSettings;

  SECTION("empty")
  {
    result = generateUnprotectedField("", csvSettings);
    REQUIRE( result == "" );
  }

  SECTION("space")
  {
    REQUIRE( generateUnprotectedFieldFails(" ", csvSettings) );
  }

  SECTION("space A")
  {
    REQUIRE( generateUnprotectedFieldFails(" A", csvSettings) );
  }

  SECTION("A space")
  {
    REQUIRE( generateUnprotectedFieldFails("A ", csvSettings) );
  }

  SECTION("space A space")
  {
    REQUIRE( generateUnprotectedFieldFails(" A ", csvSettings) );
  }

  SECTION("A")
  {
    result = generateUnprotectedField("A", csvSettings);
    REQUIRE( result == "A" );
  }

  SECTION("AB")
  {
    result = generateUnprotectedField("AB", csvSettings);
    REQUIRE( result == "AB" );
  }

  SECTION("A B")
  {
    result = generateUnprotectedField("A B", csvSettings);
    REQUIRE( result == "A B" );
  }

  SECTION("ABC")
  {
    result = generateUnprotectedField("ABC", csvSettings);
    REQUIRE( result == "ABC" );
  }

  SECTION("A B  C")
  {
    result = generateUnprotectedField("A B  C", csvSettings);
    REQUIRE( result == "A B  C" );
  }

  SECTION("A,B")
  {
    REQUIRE( generateUnprotectedFieldFails("A,B", csvSettings) );
  }

  SECTION("\"A\"")
  {
    REQUIRE( generateUnprotectedFieldFails("\"A\"", csvSettings) );
  }

  SECTION("Field separator is ,")
  {
    csvSettings.setFieldSeparator(',');

    SECTION(",")
    {
      REQUIRE( generateUnprotectedFieldFails(",", csvSettings) );
    }

    SECTION(";")
    {
      REQUIRE( !generateUnprotectedFieldFails(";", csvSettings) );
    }
  }

  SECTION("Field separator is ;")
  {
    csvSettings.setFieldSeparator(';');

    SECTION(",")
    {
      REQUIRE( !generateUnprotectedFieldFails(",", csvSettings) );
    }

    SECTION(";")
    {
      REQUIRE( generateUnprotectedFieldFails(";", csvSettings) );
    }
  }
}

TEST_CASE("UnprotectedField_EXP")
{
  std::string result;
  CsvGeneratorSettings csvSettings;

  SECTION("Add EXP")
  {
    csvSettings.setAddExp(true);

    SECTION("A")
    {
      result = generateUnprotectedField("A", csvSettings);
      REQUIRE( result == "~A" );
    }

    SECTION("~A")
    {
      result = generateUnprotectedField("~A", csvSettings);
      REQUIRE( result == "~~A" );
    }

    SECTION("A~")
    {
      result = generateUnprotectedField("A~", csvSettings);
      REQUIRE( result == "~A~" );
    }
  }

  SECTION("Do not add EXP")
  {
    csvSettings.setAddExp(false);

    SECTION("A")
    {
      result = generateUnprotectedField("A", csvSettings);
      REQUIRE( result == "A" );
    }

    SECTION("~A")
    {
      result = generateUnprotectedField("~A", csvSettings);
      REQUIRE( result == "~A" );
    }

    SECTION("A~")
    {
      result = generateUnprotectedField("A~", csvSettings);
      REQUIRE( result == "A~" );
    }
  }
}

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

  SECTION("A B")
  {
    result = generateProtectedField("A B", csvSettings);
    REQUIRE( result == "\"A B\"" );
  }

  SECTION("A B  C")
  {
    result = generateProtectedField("A B  C", csvSettings);
    REQUIRE( result == "\"A B  C\"" );
  }

  SECTION("A,B")
  {
    result = generateProtectedField("A,B", csvSettings);
    REQUIRE( result == "\"A,B\"" );
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

TEST_CASE("FieldColumn")
{
  std::string result;
  CsvGeneratorSettings csvSettings;

  SECTION("empty")
  {
    result = generateFieldColumn("", csvSettings);
    REQUIRE( result == "" );
  }

  SECTION("A")
  {
    result = generateFieldColumn("A", csvSettings);
    REQUIRE( result == "A" );
  }

  SECTION("AB")
  {
    result = generateFieldColumn("AB", csvSettings);
    REQUIRE( result == "AB" );
  }

  SECTION("ABC")
  {
    result = generateFieldColumn("ABC", csvSettings);
    REQUIRE( result == "ABC" );
  }

  SECTION("A B  C")
  {
    result = generateFieldColumn("A B  C", csvSettings);
    REQUIRE( result == "A B  C" );
  }

  SECTION("\\n")
  {
    result = generateFieldColumn("\n", csvSettings);
    REQUIRE( result == "\"\n\"" );
  }

  SECTION("\\r")
  {
    result = generateFieldColumn("\r", csvSettings);
    REQUIRE( result == "\"\r\"" );
  }

  SECTION("\\r\\n")
  {
    result = generateFieldColumn("\r\n", csvSettings);
    REQUIRE( result == "\"\r\n\"" );
  }

  SECTION("\"A\"")
  {
    result = generateFieldColumn("\"A\"", csvSettings);
    REQUIRE( result == "\"\"\"A\"\"\"" );
  }

  SECTION("Field separator is ,")
  {
    csvSettings.setFieldSeparator(',');

    SECTION(",")
    {
      result = generateFieldColumn(",", csvSettings);
      REQUIRE( result == "\",\"" );
    }

    SECTION(";")
    {
      result = generateFieldColumn(";", csvSettings);
      REQUIRE( result == ";" );
    }
  }

  SECTION("Field separator is ;")
  {
    csvSettings.setFieldSeparator(';');

    SECTION(",")
    {
      result = generateFieldColumn(",", csvSettings);
      REQUIRE( result == "," );
    }

    SECTION(";")
    {
      result = generateFieldColumn(";", csvSettings);
      REQUIRE( result == "\";\"" );
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
