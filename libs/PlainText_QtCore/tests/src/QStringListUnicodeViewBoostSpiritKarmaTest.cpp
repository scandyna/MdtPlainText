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
#include "QStringListUnicodeViewTestCommon.h"
#include <boost/spirit/include/karma.hpp>

template<typename FieldColumnRule>
bool generateToStdString(const QStringList & record, const FieldColumnRule & fieldColumn, std::string & destination)
{
//   using KarmaRecord = Mdt::PlainText::BoostSpiritKarmaQStringRecord<std::vector<QString>>;

  const QStringListUnicodeView sourceContainer(record);

  boost::spirit::karma::rule<std::back_insert_iterator<std::string>, QStringListUnicodeView()> csvRecord;
  csvRecord = fieldColumn % ',';

  return boost::spirit::karma::generate(std::back_inserter(destination), csvRecord, sourceContainer);
}


TEST_CASE("standard_char_")
{
  using boost::spirit::standard::char_;

  std::string result;

  SECTION("A")
  {
//     REQUIRE( generateToStdString({QLatin1String("A")}, *char_, result) );
    REQUIRE( result == "A" );
  }

  REQUIRE(false);
}
