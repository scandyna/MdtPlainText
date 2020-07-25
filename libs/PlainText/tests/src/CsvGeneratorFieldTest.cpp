/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "catch2/catch.hpp"
#include "Mdt/PlainText/CsvGeneratorField.h"
#include <vector>

using namespace Mdt::PlainText;
using Record = std::vector<CsvGeneratorField>;

TEST_CASE("constructField")
{
  CsvGeneratorField field1("A");
  REQUIRE( field1.haveToProtect() );
  REQUIRE( field1.value() == "A" );

  CsvGeneratorField field2("B", CsvGeneratorField::DoNotProtect);
  REQUIRE( !field2.haveToProtect() );
  REQUIRE( field2.value() == "B" );

  CsvGeneratorField field3{"C"};
  REQUIRE( field3.haveToProtect() );
  REQUIRE( field3.value() == "C" );

  CsvGeneratorField field4{"D", CsvGeneratorField::DoNotProtect};
  REQUIRE( !field4.haveToProtect() );
  REQUIRE( field4.value() == "D" );
}

TEST_CASE("doProtect")
{
  CsvGeneratorField field("A", CsvGeneratorField::DoNotProtect);
  field.doProtect();
  REQUIRE( field.haveToProtect() );
}

TEST_CASE("doNotProtect")
{
  CsvGeneratorField field("A", CsvGeneratorField::DoProtect);
  field.doNotProtect();
  REQUIRE( !field.haveToProtect() );
}

TEST_CASE("constructRecord")
{
  Record record1{{"A"},{"B"},{"C"}};
  REQUIRE( record1[0].value() == "A" );
  REQUIRE( record1[0].haveToProtect() );

  Record record2{
    {"A", CsvGeneratorField::DoProtect},
    {"B", CsvGeneratorField::DoNotProtect}
  };
  REQUIRE( record2[0].value() == "A" );
  REQUIRE( record2[0].haveToProtect() );
  REQUIRE( record2[1].value() == "B" );
  REQUIRE( !record2[1].haveToProtect() );
}
