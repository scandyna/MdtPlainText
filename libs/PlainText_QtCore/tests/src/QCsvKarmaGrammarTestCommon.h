/****************************************************************************
 **
 ** MdtPlainText - A C++ library to read and write simple plain text
 ** using the boost Spirit library.
 **
 ** Copyright (C) 2020-2020 Philippe Steinmann.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with this program.  If not, see <https://www.gnu.org/licenses/>.
 **
 ****************************************************************************/
#include "catch2/catch.hpp"
#include "Mdt/PlainText/CsvGeneratorSettings.h"
#include "Mdt/PlainText/Grammar/Csv/Karma/ProtectedField.h"
#include "Mdt/PlainText/Grammar/Csv/Karma/CsvFileLine.h"
#include "Mdt/PlainText/BoostSpiritQStringContainer.h"
#include <boost/spirit/include/karma.hpp>
#include <QString>
#include <QLatin1String>
#include <vector>
#include <iterator>
#include <cassert>

using namespace Mdt::PlainText;

using ProtectedField = Grammar::Csv::Karma::ProtectedField<std::back_insert_iterator<QString>, QString>;


template<typename Rule>
bool generateRuleFails(const QString & data, const CsvGeneratorSettings & settings)
{
  assert( settings.isValid() );

  Rule rule(settings);

  return !boost::spirit::karma::generate(rule, data);
}

// template<typename Rule>
// QString generateFromQStringRule(const QString & data, const CsvGeneratorSettings & settings)
// {
//   assert( settings.isValid() );
// 
//   QString result;
//   Rule rule(settings);
// 
//   const bool ok = boost::spirit::karma::generate(std::back_inserter(result), rule, data);
//   if(!ok){
//     const std::string what = "Rule '" + rule.name() + "' failed to generate from '" + data + "'";
//     throw std::runtime_error(what);
//   }
// 
//   return result;
// }


// bool generateProtectedFieldFails(const QString & data, const CsvGeneratorSettings & settings)
// {
//   assert( settings.isValid() );
// 
//   return generateRuleFails<ProtectedField>(data, settings);
// }

// QString generateProtectedField(const QString & data, const CsvGeneratorSettings & settings)
// {
//   assert( settings.isValid() );
// 
//   return generateFromQStringRule<ProtectedField>(data, settings);
// }
