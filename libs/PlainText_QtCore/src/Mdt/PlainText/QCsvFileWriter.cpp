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
#include "QCsvFileWriter.h"
#include "QCsvFileWriterTemplate.h"
#include <cassert>

namespace Mdt{ namespace PlainText{

QCsvFileWriter::QCsvFileWriter()
 : mImpl( std::make_unique<QCsvFileWriterTemplate>() )
{
}

QCsvFileWriter::~QCsvFileWriter()
{
}

void QCsvFileWriter::setFilePath(const QString & filePath)
{
  assert( !filePath.isEmpty() );
  assert( !isOpen() );

  mImpl->setFilePath(filePath);
}

QString QCsvFileWriter::filePath() const
{
  return mImpl->filePath();
}

void QCsvFileWriter::setFileEncoding(const QByteArray & encoding)
{
  Q_ASSERT( !encoding.isEmpty() );
  assert( !isOpen() );

  mImpl->setFileEncoding(encoding);
}

const QByteArray & QCsvFileWriter::fileEncoding() const noexcept
{
  return mImpl->fileEncoding();
}

void QCsvFileWriter::setCsvSettings(const CsvGeneratorSettings & settings) noexcept
{
  assert( settings.isValid() );
  assert( !isOpen() );

  mImpl->setCsvSettings(settings);
}

const CsvGeneratorSettings & QCsvFileWriter::csvSettings() const noexcept
{
  return mImpl->csvSettings();
}

void QCsvFileWriter::setOpenMode(FileWriteOpenMode mode)
{
  assert( !isOpen() );

  mImpl->setOpenMode(mode);
}

FileWriteOpenMode QCsvFileWriter::openMode() const noexcept
{
  return mImpl->openMode();
}

void QCsvFileWriter::open()
{
  assert( !filePath().isEmpty() );

  mImpl->open();
}

bool QCsvFileWriter::isOpen() const
{
  return mImpl->isOpen();
}


void QCsvFileWriter::close()
{
  mImpl->close();
}

}} // namespace Mdt{ namespace PlainText{
