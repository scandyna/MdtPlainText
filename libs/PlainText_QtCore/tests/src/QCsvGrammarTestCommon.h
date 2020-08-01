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
#include "Mdt/PlainText/Grammar/Csv/FieldColumn.h"
#include "Mdt/PlainText/Grammar/Csv/CsvRecord.h"
#include "Mdt/PlainText/Grammar/Csv/CsvFile.h"
#include "Mdt/PlainText/BoostSpiritQStringConstIterator.h"
#include "Mdt/PlainText/BoostSpiritQStringContainer.h"
#include "Mdt/PlainText/CsvParserSettings.h"
#include "Mdt/PlainText/QRuntimeError.h"
#include <QString>
#include <QStringList>
#include <QLatin1String>
#include <QDebug>
#include <string>
#include <vector>

using namespace Mdt::PlainText;

using StringTable = std::vector<QStringList>;

QString parseFieldColumn(const QString & sourceString, const CsvParserSettings & settings)
{
  Q_ASSERT( settings.isValid() );

  QString data;
  Mdt::PlainText::Grammar::Csv::FieldColumn<BoostSpiritQStringConstIterator, QString> rule(settings);

  BoostSpiritQStringConstIterator first( sourceString.cbegin(), sourceString.cend() );
  BoostSpiritQStringConstIterator last( sourceString.cend(), sourceString.cend() );
  const bool ok = boost::spirit::qi::parse(first, last, rule, data);
  if(!ok){
    const QString what = QLatin1String("Failed to parse a field column from ") + sourceString;
    throw QRuntimeError(what);
  }

  return data;
}

QStringList parseRecord(const QString & sourceString, const CsvParserSettings & settings)
{
  assert( settings.isValid() );

  QStringList record;
  Mdt::PlainText::Grammar::Csv::CsvRecord<BoostSpiritQStringConstIterator, QStringList> rule(settings);

  BoostSpiritQStringConstIterator first( sourceString.cbegin(), sourceString.cend() );
  BoostSpiritQStringConstIterator last( sourceString.cend(), sourceString.cend() );
  const bool ok = boost::spirit::qi::parse(first, last, rule, record);
  if(!ok){
    const QString what = QLatin1String("Failed to parse a record from ") + sourceString;
    throw QRuntimeError(what);
  }

  return record;
}

bool qStringListEqualsUtf8StringList(const QStringList & list, const std::vector<std::string> & refList)
{
  if( list.size() != (int)refList.size() ){
    qDebug() << "list size(" << list.size() << ") differs from expected list size: " << refList.size();
    return false;
  }
  for(int i=0; i < list.size(); ++i){
    if(list.at(i).toStdString() != refList[i]){
      qDebug() << "list[" << i << "] differs from reference. Str: " << list.at(i) << ", expected: " << QString::fromStdString(refList[i]);
      return false;
    }
  }

  return true;
}

StringTable parseCsvFileRuleString(const QString & sourceString, const CsvParserSettings & settings)
{
  StringTable table;
  Mdt::PlainText::Grammar::Csv::CsvFile<BoostSpiritQStringConstIterator, StringTable> rule(settings);

  BoostSpiritQStringConstIterator first( sourceString.cbegin(), sourceString.cend() );
  BoostSpiritQStringConstIterator last( sourceString.cend(), sourceString.cend() );
  const bool ok = boost::spirit::qi::parse(first, last, rule, table);
  if(!ok){
    const QString what = QLatin1String("Failed to parse table from ") + sourceString;
    throw QRuntimeError(what);
  }

  return table;
}

bool qStringTableEqualsUtf8StringTable(const StringTable & table, const std::vector< std::vector<std::string> > & refTable)
{
  if( table.size() != refTable.size() ){
    qDebug() << "table size(" << table.size() << ") differs from expected table size: " << refTable.size();
    return false;
  }
  for(size_t row = 0; row < table.size(); ++row){
    if(table[row].size() != (int)refTable[row].size()){
      qDebug() << "table's row " << row << " column count (" << table[row].size() << ") differs from expected one: " << refTable[row].size();
      return false;
    }
    for(int col = 0; col < table[row].size(); ++col){
      if(table[row].at(col).toStdString() != refTable[row][col]){
        qDebug() << "table[" << row << "][" << col << "] differs from reference. Str: " << table[row].at(col)
                 << ", expected: " << QString::fromStdString(refTable[row][col]);
        return false;
      }
    }
  }

  return true;
}
