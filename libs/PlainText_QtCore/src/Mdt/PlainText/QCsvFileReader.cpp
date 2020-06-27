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

namespace Mdt{ namespace PlainText{

QCsvFileReader::QCsvFileReader()
{
}

QCsvFileReader::~QCsvFileReader()
{
}

void QCsvFileReader::setFilePath(const QString & filePath)
{
  Q_ASSERT( !filePath.isEmpty() );
  Q_ASSERT( !isOpen() );
}

const QString & QCsvFileReader::filePath() const noexcept
{
}

void QCsvFileReader::setCsvSettings(const CsvParserSettings & settings) noexcept
{
  Q_ASSERT( settings.isValid() );
  Q_ASSERT( !isOpen() );
}

const CsvParserSettings & QCsvFileReader::csvSettings() const noexcept
{
}

void QCsvFileReader::open()
{
  Q_ASSERT( !filePath().isEmpty() );
}

bool QCsvFileReader::isOpen() const
{
}

bool QCsvFileReader::atEnd() const noexcept
{
  Q_ASSERT( isOpen() );
}

QStringList QCsvFileReader::readLine() const
{
  Q_ASSERT( isOpen() );
  Q_ASSERT( !atEnd() );
}

std::vector<QStringList> QCsvFileReader::readAll() const
{
  Q_ASSERT( isOpen() );
  Q_ASSERT( !atEnd() );

}

void QCsvFileReader::close()
{
}

}} // namespace Mdt{ namespace PlainText{
