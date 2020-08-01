/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "CsvFileWriter.h"
#include "CsvFileWriterTemplate.h"
#include <cassert>

namespace Mdt{ namespace PlainText{

CsvFileWriter::CsvFileWriter()
 : mImpl( std::make_unique<CsvFileWriterTemplate>() )
{
}

CsvFileWriter::~CsvFileWriter()
{
}

void CsvFileWriter::setFilePath(const std::string & filePath)
{
  assert( !filePath.empty() );
  assert( !isOpen() );

  mImpl->setFilePath(filePath);
}

const std::string & CsvFileWriter::filePath() const noexcept
{
  return mImpl->filePath();
}

void CsvFileWriter::setCsvSettings(const CsvGeneratorSettings & settings) noexcept
{
  assert( settings.isValid() );
  assert( !isOpen() );

  mImpl->setCsvSettings(settings);
}

const CsvGeneratorSettings & CsvFileWriter::csvSettings() const noexcept
{
  return mImpl->csvSettings();
}

void CsvFileWriter::setOpenMode(FileWriteOpenMode mode)
{
  assert( !isOpen() );

  mImpl->setOpenMode(mode);
}

FileWriteOpenMode CsvFileWriter::openMode() const noexcept
{
  return mImpl->openMode();
}

void CsvFileWriter::open()
{
  assert( !filePath().empty() );

  mImpl->open();
}

bool CsvFileWriter::isOpen() const
{
  return mImpl->isOpen();
}

void CsvFileWriter::appendLine(const std::vector<CsvGeneratorField> & record)
{
  assert( isOpen() );
}

void CsvFileWriter::close()
{
  mImpl->close();
}

}} // namespace Mdt{ namespace PlainText{
