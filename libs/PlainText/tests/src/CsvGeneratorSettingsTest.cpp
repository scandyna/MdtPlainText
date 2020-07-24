/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "catch2/catch.hpp"
#include "Mdt/PlainText/CsvGeneratorSettings.h"

using namespace Mdt::PlainText;

TEST_CASE("default")
{
  CsvGeneratorSettings settings;
  REQUIRE( settings.fieldSeparator() == ',' );
  REQUIRE( settings.fieldProtection() == '"' );
  REQUIRE( !settings.addExp() );
  REQUIRE( settings.endOfLine() == EndOfLine::Native );
}

TEST_CASE("set_get")
{
  CsvGeneratorSettings settings;

  settings.setFieldSeparator(';');
  REQUIRE( settings.fieldSeparator() == ';' );

  settings.setFieldProtection('\'');
  REQUIRE( settings.fieldProtection() == '\'' );

  settings.setAddExp(true);
  REQUIRE( settings.addExp() );

  settings.setEndOfLine(EndOfLine::Lf);
  REQUIRE( settings.endOfLine() == EndOfLine::Lf );
}

TEST_CASE("isEndOfLine")
{
  SECTION("\\n")
  {
    REQUIRE( CsvGeneratorSettings::isEndOfLine('\n') );
  }

  SECTION("\\r")
  {
    REQUIRE( CsvGeneratorSettings::isEndOfLine('\r') );
  }

  SECTION(",")
  {
    REQUIRE( !CsvGeneratorSettings::isEndOfLine(',') );
  }

  SECTION(";")
  {
    REQUIRE( !CsvGeneratorSettings::isEndOfLine(';') );
  }

  SECTION("'")
  {
    REQUIRE( !CsvGeneratorSettings::isEndOfLine('\'') );
  }

  SECTION("\"")
  {
    REQUIRE( !CsvGeneratorSettings::isEndOfLine('"') );
  }
}

TEST_CASE("validate")
{
  CsvGeneratorSettings settings;
  settings.setAddExp(false);

  SECTION("default")
  {
    REQUIRE( settings.validate() == CsvGeneratorSettingsValidity::Valid );
    REQUIRE( settings.isValid() );
  }

  SECTION("valid , \"")
  {
    settings.setFieldSeparator(',');
    settings.setFieldProtection('"');
    REQUIRE( settings.validate() == CsvGeneratorSettingsValidity::Valid );
    REQUIRE( settings.isValid() );
  }

  SECTION("invalid , ,")
  {
    settings.setFieldSeparator(',');
    settings.setFieldProtection(',');
    REQUIRE( settings.validate() == CsvGeneratorSettingsValidity::FieldSeparatorAndProtectionAreSame );
    REQUIRE( !settings.isValid() );
  }

  SECTION("invalid \" \"")
  {
    settings.setFieldSeparator('"');
    settings.setFieldProtection('"');
    REQUIRE( settings.validate() == CsvGeneratorSettingsValidity::FieldSeparatorAndProtectionAreSame );
    REQUIRE( !settings.isValid() );
  }

  SECTION("valid ~ ,")
  {
    settings.setFieldSeparator('~');
    settings.setFieldProtection(',');
    REQUIRE( settings.validate() == CsvGeneratorSettingsValidity::Valid );
    REQUIRE( settings.isValid() );

  }

  SECTION("valid , ~")
  {
    settings.setFieldSeparator(',');
    settings.setFieldProtection('~');
    REQUIRE( settings.validate() == CsvGeneratorSettingsValidity::Valid );
    REQUIRE( settings.isValid() );
  }

  SECTION("invalid , ~ EXP")
  {
    settings.setFieldSeparator(',');
    settings.setFieldProtection('~');
    settings.setAddExp(true);
    REQUIRE( settings.validate() == CsvGeneratorSettingsValidity::FieldProtectionIsEXP );
    REQUIRE( !settings.isValid() );
  }

  SECTION("invalid ~ , EXP")
  {
    settings.setFieldSeparator('~');
    settings.setFieldProtection(',');
    settings.setAddExp(true);
    REQUIRE( settings.validate() == CsvGeneratorSettingsValidity::FieldSeparatorIsEXP );
    REQUIRE( !settings.isValid() );
  }

  SECTION("invalid , , EXP")
  {
    settings.setFieldSeparator(',');
    settings.setFieldProtection(',');
    settings.setAddExp(true);
    REQUIRE( settings.validate() == CsvGeneratorSettingsValidity::FieldSeparatorAndProtectionAreSame );
    REQUIRE( !settings.isValid() );
  }

  SECTION("valid , \" EXP")
  {
    settings.setFieldSeparator(',');
    settings.setFieldProtection('"');
    settings.setAddExp(true);
    REQUIRE( settings.validate() == CsvGeneratorSettingsValidity::Valid );
    REQUIRE( settings.isValid() );
  }
}
