/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "catch2/catch.hpp"
#include "Mdt/PlainText/Grammar/Csv/UnprotectedField.h"
#include "Mdt/PlainText/Grammar/Csv/NonEmptyUnprotectedField.h"
#include "Mdt/PlainText/Grammar/Csv/FieldColumn.h"
#include "Mdt/PlainText/Grammar/Csv/RecordRule.h"
#include "Mdt/PlainText/Grammar/Csv/CsvFileRule.h"
#include "Mdt/PlainText/CsvParserSettings"
#include <boost/spirit/include/qi.hpp>
#include <string>
#include <utility>
#include <vector>
#include <stdexcept>
#include <cassert>

using namespace Mdt::PlainText;

using StringRecord = std::vector<std::string>;
using StringTable = std::vector<StringRecord>;

using UnprotectedField = Grammar::Csv::UnprotectedField<std::string::const_iterator, std::string>;
using NonEmptyUnprotectedField = Grammar::Csv::NonEmptyUnprotectedField<std::string::const_iterator, std::string>;
using FieldColumn = Grammar::Csv::FieldColumn<std::string::const_iterator, std::string>;

using RecordRule = Grammar::Csv::RecordRule<std::string::const_iterator, StringRecord>;

/*
 * Used for GENERATE( values<> )
 */
struct InputExpectedStringData
{
  std::string input;
  std::string expected;
};

template<typename Rule>
bool parseRuleFails(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  Rule rule(settings);

  return !boost::spirit::qi::parse(sourceString.cbegin(), sourceString.cend(), rule);
}

template<typename Rule>
std::string parseToStringRule(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  std::string data;
  Rule rule(settings);

  const bool ok = boost::spirit::qi::parse(sourceString.cbegin(), sourceString.cend(), rule, data);
  if(!ok){
    const std::string what = "Rule " + rule.name() + " failed to parse " + sourceString;
    throw std::runtime_error(what);
  }

  return data;
}

template<typename Rule>
StringRecord parseToStringRecordRule(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  StringRecord record;
  Rule rule(settings);

  const bool ok = boost::spirit::qi::parse(sourceString.cbegin(), sourceString.cend(), rule, record);
  if(!ok){
    const std::string what = "Rule " + rule.name() + " failed to parse " + sourceString;
    throw std::runtime_error(what);
  }

  return record;
}


bool parseUnprotectedFieldFails(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  return parseRuleFails<UnprotectedField>(sourceString, settings);
}

std::string parseUnprotectedField(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  return parseToStringRule<UnprotectedField>(sourceString, settings);
}

bool parseNonEmptyUnprotectedFieldFails(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  return parseRuleFails<NonEmptyUnprotectedField>(sourceString, settings);
}

std::string parseNonEmptyUnprotectedField(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  return parseToStringRule<NonEmptyUnprotectedField>(sourceString, settings);
}

std::string parseFieldColumn(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  return parseToStringRule<FieldColumn>(sourceString, settings);
}

StringRecord parseRecord(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  return parseToStringRecordRule<RecordRule>(sourceString, settings);
}

StringTable parseCsvFileRuleString(const std::string & sourceString, const CsvParserSettings & settings)
{
  StringTable table;
  Mdt::PlainText::Grammar::Csv::CsvFileRule<std::string::const_iterator, StringTable> rule(settings);

  const bool ok = boost::spirit::qi::parse(sourceString.cbegin(), sourceString.cend(), rule, table);
  if(!ok){
    const std::string what = "Failed to parse table from " + sourceString;
    throw std::runtime_error(what);
  }

  return table;
}
