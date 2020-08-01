/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "catch2/catch.hpp"
#include "Mdt/PlainText/CsvGeneratorSettings.h"
#include "Mdt/PlainText/Grammar/Csv/Karma/ProtectedField.h"
#include "Mdt/PlainText/Grammar/Csv/Karma/CsvFileLine.h"
#include <boost/spirit/include/karma.hpp>
#include <string>
#include <vector>
#include <iterator>
#include <cassert>

using namespace Mdt::PlainText;

/// \todo Should also use CsvGeneratorField !

using StringRecord = std::vector<std::string>;
using StringTable = std::vector<StringRecord>;

using ProtectedField = Grammar::Csv::Karma::ProtectedField<std::back_insert_iterator<std::string>, std::string>;
using CsvFileLine = Grammar::Csv::Karma::CsvFileLine<std::back_insert_iterator<std::string>, StringRecord>;



template<typename Rule>
bool generateRuleFails(const std::string & data, const CsvGeneratorSettings & settings)
{
  assert( settings.isValid() );

  Rule rule(settings);

  return !boost::spirit::karma::generate(rule, data);
}

template<typename Rule>
std::string generateFromStringRule(const std::string & data, const CsvGeneratorSettings & settings)
{
  assert( settings.isValid() );

  std::string result;
  Rule rule(settings);

  const bool ok = boost::spirit::karma::generate(std::back_inserter(result), rule, data);
  if(!ok){
    const std::string what = "Rule '" + rule.name() + "' failed to generate from '" + data + "'";
    throw std::runtime_error(what);
  }

  return result;
}

template<typename Rule>
std::string generateFromStringRecordRule(const StringRecord & data, const CsvGeneratorSettings & settings)
{
  assert( settings.isValid() );

  std::string result;
  Rule rule(settings);

  const bool ok = boost::spirit::karma::generate(std::back_inserter(result), rule, data);
  if(!ok){
    const std::string what = "Rule '" + rule.name() + "' failed to generate";
    throw std::runtime_error(what);
  }

  return result;
}


bool generateProtectedFieldFails(const std::string & data, const CsvGeneratorSettings & settings)
{
  assert( settings.isValid() );

  return generateRuleFails<ProtectedField>(data, settings);
}

std::string generateProtectedField(const std::string & data, const CsvGeneratorSettings & settings)
{
  assert( settings.isValid() );

  return generateFromStringRule<ProtectedField>(data, settings);
}

std::string generateCsvFileLineString(const StringRecord & data, const CsvGeneratorSettings & settings)
{
  assert( settings.isValid() );

  return generateFromStringRecordRule<CsvFileLine>(data, settings);
}
