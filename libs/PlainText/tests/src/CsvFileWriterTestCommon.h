/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "catch2/catch.hpp"
#include "Mdt/PlainText/CsvFileWriter"
#include "Mdt/PlainText/TestLib/TextFileUtils.h"
#include <QTemporaryDir>
#include <QDir>
#include <QString>
#include <QLatin1String>
#include <QLatin1Char>
#include <QByteArray>
#include <cassert>

using namespace Mdt::PlainText;

QString filePathFromDirAndFileName(const QTemporaryDir & dir, const char *fileName)
{
  assert( dir.isValid() );

  return QDir::cleanPath( dir.path() + QLatin1Char('/') + QLatin1String(fileName) );
}

void setFilePathToWriter(const QString & filePath, CsvFileWriter & writer)
{
  writer.setFilePath( filePath.toLocal8Bit().toStdString() );
}

void setDirectoryPathToWriter(const QTemporaryDir & dir, CsvFileWriter & writer)
{
  assert( dir.isValid() );

  setFilePathToWriter(dir.path(), writer);
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
