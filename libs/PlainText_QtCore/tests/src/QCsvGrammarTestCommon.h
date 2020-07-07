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
#include "Mdt/PlainText/Grammar/Csv/FieldColumnRule.h"
#include "Mdt/PlainText/Grammar/Csv/RecordRule.h"
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


QString parseFieldColumn(const QString & sourceString, const CsvParserSettings & settings)
{
  Q_ASSERT( settings.isValid() );

  QString data;
  Mdt::PlainText::Grammar::Csv::FieldColumnRule<BoostSpiritQStringConstIterator, QString> rule(settings);

  BoostSpiritQStringConstIterator first( sourceString.cbegin() );
  BoostSpiritQStringConstIterator last( sourceString.cend() );
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
  Mdt::PlainText::Grammar::Csv::RecordRule<BoostSpiritQStringConstIterator, QStringList> rule(settings);

  BoostSpiritQStringConstIterator first( sourceString.cbegin() );
  BoostSpiritQStringConstIterator last( sourceString.cend() );
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
