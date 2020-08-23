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
#include "Mdt/PlainText/QStringListUnicodeView"
#include <QString>
#include <QStringList>
#include <QLatin1String>
#include <string>
#include <vector>
#include <iterator>
#include <type_traits>

using Mdt::PlainText::QStringListUnicodeView;
using Mdt::PlainText::QStringUnicodeView;

QStringList qStringListFromStdStringList(const std::vector<std::string> & stdStringList)
{
  QStringList stringList;

  for(const std::string & str : stdStringList){
    stringList.append( QString::fromStdString(str) );
  }

  return stringList;
}

bool unicodeStringViewEqualsLatin1String(const QStringUnicodeView & s1, const std::string & s2)
{
  return s1.toQString().toStdString() == s2;
}
