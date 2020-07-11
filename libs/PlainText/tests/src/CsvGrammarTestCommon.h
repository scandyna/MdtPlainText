/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "catch2/catch.hpp"
#include "Mdt/PlainText/Grammar/Csv/UnprotectedField.h"
#include "Mdt/PlainText/Grammar/Csv/NonEmptyUnprotectedField.h"
#include "Mdt/PlainText/Grammar/Csv/FieldColumnRule.h"
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

/*
 * Used for GENERATE( values<> )
 */
struct InputExpectedStringData {
  std::string input;
  std::string expected;
};

bool parseUnprotectedFieldFails(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  Mdt::PlainText::Grammar::Csv::UnprotectedField<std::string::const_iterator, std::string> rule(settings);

  return !boost::spirit::qi::parse(sourceString.cbegin(), sourceString.cend(), rule);
}

std::string parseUnprotectedField(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  std::string data;
  Mdt::PlainText::Grammar::Csv::UnprotectedField<std::string::const_iterator, std::string> rule(settings);

  const bool ok = boost::spirit::qi::parse(sourceString.cbegin(), sourceString.cend(), rule, data);
  if(!ok){
    const std::string what = "Failed to parse a field from " + sourceString;
    throw std::runtime_error(what);
  }

  return data;
}

bool parseNonEmptyUnprotectedFieldFails(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  Mdt::PlainText::Grammar::Csv::NonEmptyUnprotectedField<std::string::const_iterator, std::string> rule(settings);

  return !boost::spirit::qi::parse(sourceString.cbegin(), sourceString.cend(), rule);
}

std::string parseNonEmptyUnprotectedField(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  std::string data;
  Mdt::PlainText::Grammar::Csv::NonEmptyUnprotectedField<std::string::const_iterator, std::string> rule(settings);

  const bool ok = boost::spirit::qi::parse(sourceString.cbegin(), sourceString.cend(), rule, data);
  if(!ok){
    const std::string what = "Failed to parse a field from " + sourceString;
    throw std::runtime_error(what);
  }

  return data;
}

std::string parseFieldColumn(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  std::string data;
  Mdt::PlainText::Grammar::Csv::FieldColumnRule<std::string::const_iterator, std::string> rule(settings);

  const bool ok = boost::spirit::qi::parse(sourceString.cbegin(), sourceString.cend(), rule, data);
  if(!ok){
    const std::string what = "Failed to parse a field column from " + sourceString;
    throw std::runtime_error(what);
  }

  return data;
}

StringRecord parseRecord(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  StringRecord record;
  Mdt::PlainText::Grammar::Csv::RecordRule<std::string::const_iterator, StringRecord> rule(settings);

  const bool ok = boost::spirit::qi::parse(sourceString.cbegin(), sourceString.cend(), rule, record);
  if(!ok){
    const std::string what = "Failed to parse a record from " + sourceString;
    throw std::runtime_error(what);
  }

  return record;
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
