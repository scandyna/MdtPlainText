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
#include "Mdt/PlainText/QCsvFileWriter"
#include "Mdt/PlainText/TestLib/TextFileUtils.h"
#include <QLatin1String>
#include <QLatin1Char>
#include <QString>
#include <QTemporaryDir>
#include <vector>
#include <string>

using namespace Mdt::PlainText;

QString filePathFromDirAndFileName(const QTemporaryDir & dir, const char *fileName)
{
  assert( dir.isValid() );

  return QDir::cleanPath( dir.path() + QLatin1Char('/') + QLatin1String(fileName) );
}

void setDirectoryPathToWriter(const QTemporaryDir & dir, QCsvFileWriter & writer)
{
  writer.setFilePath( dir.path() );
}

bool fileExists(const QString & filePath)
{
  return Mdt::PlainText::TestLib::fileExists(filePath);
}

bool writeTextFile(const QString & filePath, const QString & content)
{
  return Mdt::PlainText::TestLib::writeTextFileUtf8(filePath, content);
}

QString readTextFile(const QString & filePath)
{
  return Mdt::PlainText::TestLib::readTextFileUtf8(filePath);
}

QStringList qStringListFromStdStringList(const std::vector<std::string> & stdStringList)
{
  QStringList stringList;

  for(const std::string & str : stdStringList){
    stringList.append( QString::fromStdString(str) );
  }

  return stringList;
}

std::vector<QStringList> qStringTableFromStdStringTable(const std::vector< std::vector<std::string> > & stdStringTable)
{
  std::vector<QStringList> table;

  for(const auto & record : stdStringTable){
    table.push_back( qStringListFromStdStringList(record) );
  }

  return table;
}
