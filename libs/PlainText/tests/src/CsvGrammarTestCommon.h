/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "catch2/catch.hpp"
#include "Mdt/PlainText/Grammar/Csv/FieldColumnRule.h"
#include "Mdt/PlainText/Grammar/Csv/RecordRule.h"
#include "Mdt/PlainText/CsvParserSettings"
#include <boost/spirit/include/qi.hpp>
#include <string>
#include <vector>
#include <stdexcept>
#include <cassert>

using namespace Mdt::PlainText;

using StringRecord = std::vector<std::string>;


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
