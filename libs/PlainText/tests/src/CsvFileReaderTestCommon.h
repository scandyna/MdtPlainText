/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "catch2/catch.hpp"
#include "Mdt/PlainText/CsvFileReader"
#include <QTemporaryFile>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTemporaryDir>
#include <QString>
#include <QLatin1String>
#include <QTextStream>
#include <QByteArray>

using namespace Mdt::PlainText;

bool writeTextFile(QFile & file, const QString & content)
{
  Q_ASSERT( file.isOpen() );
  Q_ASSERT( file.isWritable() );

  QTextStream out(&file);
  out << content;

  return true;
}

bool writeSimpleCsvFile(QFile & file)
{
  Q_ASSERT( file.isOpen() );
  Q_ASSERT( file.isWritable() );

  return writeTextFile(file, QLatin1String("A,B,C\nd,e,f"));
}

void setFilePathToReader(const QFile & file, CsvFileReader & reader)
{
  reader.setFilePath( file.fileName().toLocal8Bit().toStdString() );
}

void setTestFilePathToReader(const char *testFileName, CsvFileReader & reader)
{
  const QString filePath = QDir::cleanPath( QString::fromLocal8Bit(TEST_FILES_DIR) + '/' + QLatin1String(testFileName) );
  Q_ASSERT( QFileInfo::exists(filePath) );

  reader.setFilePath( filePath.toLocal8Bit().toStdString() );
}

void setDirectoryPathToReader(const QTemporaryDir & dir, CsvFileReader & reader)
{
  reader.setFilePath( dir.path().toLocal8Bit().toStdString() );
}
