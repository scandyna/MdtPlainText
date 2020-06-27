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

const QString & QCsvFileReader::filePath() const noexcept
{
  return mImpl->filePath();
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

QStringList QCsvFileReader::readLine() const
{
  Q_ASSERT( isOpen() );
  Q_ASSERT( !atEnd() );

  return mImpl->readLine<QStringList>();
}

std::vector<QStringList> QCsvFileReader::readAll() const
{
  Q_ASSERT( isOpen() );
  Q_ASSERT( !atEnd() );

  return mImpl->readAll< std::vector<QStringList> >();
}

void QCsvFileReader::close()
{
  mImpl->close();
}

}} // namespace Mdt{ namespace PlainText{
