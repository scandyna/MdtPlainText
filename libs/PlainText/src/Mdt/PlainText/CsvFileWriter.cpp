/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "CsvFileWriter.h"
#include <cassert>

namespace Mdt{ namespace PlainText{

CsvFileWriter::CsvFileWriter()
{
}

CsvFileWriter::~CsvFileWriter()
{
}

void CsvFileWriter::setFilePath(const std::string & filePath)
{
  assert( !filePath.empty() );
  assert( !isOpen() );
}

const std::string & CsvFileWriter::filePath() const noexcept
{
}

void CsvFileWriter::setCsvSettings(const CsvGeneratorSettings & settings) noexcept
{
  assert( settings.isValid() );
  assert( !isOpen() );
}

const CsvGeneratorSettings & CsvFileWriter::csvSettings() const noexcept
{
}

void CsvFileWriter::setOpenMode(FileWriteOpenMode mode)
{
  assert( !isOpen() );
}

FileWriteOpenMode CsvFileWriter::openMode() const noexcept
{
}

void CsvFileWriter::open()
{
  assert( !filePath().empty() );
}

bool CsvFileWriter::isOpen() const
{
}


void CsvFileWriter::close()
{
}

}} // namespace Mdt{ namespace PlainText{
