/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "catch2/catch.hpp"
#include "Mdt/PlainText/Grammar/Csv/Qi/SafeChar.h"
#include "Mdt/PlainText/Grammar/Csv/Qi/UnprotectedField.h"
#include "Mdt/PlainText/Grammar/Csv/Qi/NonEmptyUnprotectedField.h"
#include "Mdt/PlainText/Grammar/Csv/Qi/ProtectedField.h"
#include "Mdt/PlainText/Grammar/Csv/Qi/FieldColumn.h"
#include "Mdt/PlainText/Grammar/Csv/Qi/NonEmptyFieldColumn.h"
#include "Mdt/PlainText/Grammar/Csv/Qi/CsvRecord.h"
#include "Mdt/PlainText/Grammar/Csv/Qi/CsvFileLine.h"
#include "Mdt/PlainText/Grammar/Csv/Qi/CsvFile.h"
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

using SafeChar = Grammar::Csv::Qi::SafeChar<std::string::const_iterator, uint32_t>;
using UnprotectedField = Grammar::Csv::Qi::UnprotectedField<std::string::const_iterator, std::string>;
using NonEmptyUnprotectedField = Grammar::Csv::Qi::NonEmptyUnprotectedField<std::string::const_iterator, std::string>;
using ProtectedField = Grammar::Csv::Qi::ProtectedField<std::string::const_iterator, std::string>;
using FieldColumn = Grammar::Csv::Qi::FieldColumn<std::string::const_iterator, std::string>;
using NonEmptyFieldColumn = Grammar::Csv::Qi::NonEmptyFieldColumn<std::string::const_iterator, std::string>;
using CsvRecord = Grammar::Csv::Qi::CsvRecord<std::string::const_iterator, StringRecord>;
using CsvFileLine = Grammar::Csv::Qi::CsvFileLine<std::string::const_iterator, StringRecord>;
using CsvFile = Grammar::Csv::Qi::CsvFile<std::string::const_iterator, StringTable>;

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
    const std::string what = "Rule '" + rule.name() + "' failed to parse '" + sourceString + "'";
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
    const std::string what = "Rule '" + rule.name() + "' failed to parse '" + sourceString + "'";
    throw std::runtime_error(what);
  }

  return record;
}


bool parseSafeCharFails(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  return parseRuleFails<SafeChar>(sourceString, settings);
}

uint32_t parseSafeChar(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  uint32_t codePoint;
  SafeChar rule(settings);

  const bool ok = boost::spirit::qi::parse(sourceString.cbegin(), sourceString.cend(), rule, codePoint);
  if(!ok){
    const std::string what = "Rule '" + rule.name() + "' failed to parse '" + sourceString + "'";
    throw std::runtime_error(what);
  }

  return codePoint;
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

bool parseProtectedFieldFails(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  return parseRuleFails<ProtectedField>(sourceString, settings);
}

std::string parseProtectedField(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  return parseToStringRule<ProtectedField>(sourceString, settings);
}

std::string parseFieldColumn(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  return parseToStringRule<FieldColumn>(sourceString, settings);
}

bool parseNonEmptyFieldColumnFails(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  return parseRuleFails<NonEmptyFieldColumn>(sourceString, settings);
}

std::string parseNonEmptyFieldColumn(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  return parseToStringRule<NonEmptyFieldColumn>(sourceString, settings);
}

bool parseCsvRecordFails(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  return parseRuleFails<CsvRecord>(sourceString, settings);
}

StringRecord parseCsvRecord(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  return parseToStringRecordRule<CsvRecord>(sourceString, settings);
}

bool parseCsvFileLineStringFails(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  return parseRuleFails<CsvFileLine>(sourceString, settings);
}

StringRecord parseCsvFileLineString(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  return parseToStringRecordRule<CsvFileLine>(sourceString, settings);
}

bool parseCsvFileStringFails(const std::string & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  return parseRuleFails<CsvFile>(sourceString, settings);
}

StringTable parseCsvFileString(const std::string & sourceString, const CsvParserSettings & settings)
{
  StringTable table;
  Mdt::PlainText::Grammar::Csv::Qi::CsvFile<std::string::const_iterator, StringTable> rule(settings);

  const bool ok = boost::spirit::qi::parse(sourceString.cbegin(), sourceString.cend(), rule, table);
  if(!ok){
    const std::string what = "Failed to parse table from " + sourceString;
    throw std::runtime_error(what);
  }

  return table;
}
