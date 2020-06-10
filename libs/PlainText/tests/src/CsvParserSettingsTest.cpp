/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "catch2/catch.hpp"
#include "Mdt/PlainText/CsvParserSettings"

using namespace Mdt::PlainText;

TEST_CASE("default")
{
  CsvParserSettings settings;
  REQUIRE( settings.fieldSeparator() == ',' );
  REQUIRE( settings.fieldProtection() == '"' );
  REQUIRE( settings.parseExp() );
}

TEST_CASE("set_get")
{
  CsvParserSettings settings;

  settings.setFieldSeparator(';');
  REQUIRE( settings.fieldSeparator() == ';' );

  settings.setFieldProtection('\'');
  REQUIRE( settings.fieldProtection() == '\'' );

  settings.setParseExp(false);
  REQUIRE( !settings.parseExp() );
}

TEST_CASE("validate")
{
  CsvParserSettings settings;
  settings.setParseExp(false);

  SECTION("default")
  {
    REQUIRE( settings.validate() == CsvParserSettingsValidity::Valid );
    REQUIRE( settings.isValid() );
  }

  SECTION("valid , \"")
  {
    settings.setFieldSeparator(',');
    settings.setFieldProtection('"');
    REQUIRE( settings.validate() == CsvParserSettingsValidity::Valid );
    REQUIRE( settings.isValid() );
  }

  SECTION("invalid , ,")
  {
    settings.setFieldSeparator(',');
    settings.setFieldProtection(',');
    REQUIRE( settings.validate() == CsvParserSettingsValidity::FieldSeparatorAndProtectionAreSame );
    REQUIRE( !settings.isValid() );
  }

  SECTION("invalid \" \"")
  {
    settings.setFieldSeparator('"');
    settings.setFieldProtection('"');
    REQUIRE( settings.validate() == CsvParserSettingsValidity::FieldSeparatorAndProtectionAreSame );
    REQUIRE( !settings.isValid() );
  }

  SECTION("valid ~ ,")
  {
    settings.setFieldSeparator('~');
    settings.setFieldProtection(',');
    REQUIRE( settings.validate() == CsvParserSettingsValidity::Valid );
    REQUIRE( settings.isValid() );

  }

  SECTION("valid , ~")
  {
    settings.setFieldSeparator(',');
    settings.setFieldProtection('~');
    REQUIRE( settings.validate() == CsvParserSettingsValidity::Valid );
    REQUIRE( settings.isValid() );
  }

  SECTION("invalid , ~ EXP")
  {
    settings.setFieldSeparator(',');
    settings.setFieldProtection('~');
    settings.setParseExp(true);
    REQUIRE( settings.validate() == CsvParserSettingsValidity::FieldProtectionIsEXP );
    REQUIRE( !settings.isValid() );
  }

  SECTION("invalid ~ , EXP")
  {
    settings.setFieldSeparator('~');
    settings.setFieldProtection(',');
    settings.setParseExp(true);
    REQUIRE( settings.validate() == CsvParserSettingsValidity::FieldSeparatorIsEXP );
    REQUIRE( !settings.isValid() );
  }

  SECTION("invalid , , EXP")
  {
    settings.setFieldSeparator(',');
    settings.setFieldProtection(',');
    settings.setParseExp(true);
    REQUIRE( settings.validate() == CsvParserSettingsValidity::FieldSeparatorAndProtectionAreSame );
    REQUIRE( !settings.isValid() );
  }

  SECTION("valid , \" EXP")
  {
    settings.setFieldSeparator(',');
    settings.setFieldProtection('"');
    settings.setParseExp(true);
    REQUIRE( settings.validate() == CsvParserSettingsValidity::Valid );
    REQUIRE( settings.isValid() );
  }
}
