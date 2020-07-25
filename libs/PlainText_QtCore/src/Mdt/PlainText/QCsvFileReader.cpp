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
#include "QCsvFileReader.h"
#include "QCsvFileReaderTemplate.h"
#include "Mdt/PlainText/Grammar/Csv/CsvFileLine.h"
#include "Mdt/PlainText/Grammar/Csv/CsvFile.h"

namespace Mdt{ namespace PlainText{

QCsvFileReader::QCsvFileReader()
 : mImpl( std::make_unique<QCsvFileReaderTemplate>() )
{
}

QCsvFileReader::~QCsvFileReader()
{
}

void QCsvFileReader::setFilePath(const QString & filePath)
{
  Q_ASSERT( !filePath.isEmpty() );
  Q_ASSERT( !isOpen() );

  mImpl->setFilePath(filePath);
}

QString QCsvFileReader::filePath() const
{
  return mImpl->filePath();
}

void QCsvFileReader::setFileEncoding(const QByteArray & encoding)
{
  Q_ASSERT( !encoding.isEmpty() );
  Q_ASSERT( !isOpen() );

  mImpl->setFileEncoding(encoding);
}

const QByteArray & QCsvFileReader::fileEncoding() const noexcept
{
  return mImpl->fileEncoding();
}

void QCsvFileReader::setCsvSettings(const CsvParserSettings & settings) noexcept
{
  Q_ASSERT( settings.isValid() );
  Q_ASSERT( !isOpen() );

  mImpl->setCsvSettings(settings);
}

const CsvParserSettings & QCsvFileReader::csvSettings() const noexcept
{
  return mImpl->csvSettings();
}

void QCsvFileReader::open()
{
  Q_ASSERT( !filePath().isEmpty() );

  mImpl->open();
}

bool QCsvFileReader::isOpen() const
{
  return mImpl->isOpen();
}

bool QCsvFileReader::atEnd() const noexcept
{
  Q_ASSERT( isOpen() );

  return mImpl->atEnd();
}

QStringList QCsvFileReader::readLine()
{
  Q_ASSERT( isOpen() );
  Q_ASSERT( !atEnd() );

  using SourceIterator = QCsvFileReaderTemplate::const_iterator;

  Grammar::Csv::CsvFileLine<SourceIterator, QStringList> rule( csvSettings() );

  return mImpl->readLine<QStringList>(rule);
}

std::vector<QStringList> QCsvFileReader::readAll()
{
  Q_ASSERT( isOpen() );
  Q_ASSERT( !atEnd() );

  using SourceIterator = QCsvFileReaderTemplate::const_iterator;
  using Table = std::vector<QStringList>;

  Grammar::Csv::CsvFile<SourceIterator, Table> rule( csvSettings() );

  return mImpl->readAll<Table>(rule);
}

void QCsvFileReader::close()
{
  mImpl->close();
}

}} // namespace Mdt{ namespace PlainText{
