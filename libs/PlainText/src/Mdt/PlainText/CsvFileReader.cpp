/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "CsvFileReader.h"
#include "CsvFileReaderTemplate.h"
#include <cassert>

namespace Mdt{ namespace PlainText{

CsvFileReader::CsvFileReader()
 : mImpl( std::make_unique<CsvFileReaderTemplate>() )
{
}

CsvFileReader::~CsvFileReader()
{
}

void CsvFileReader::setFilePath(const std::string & filePath)
{
  assert( !filePath.empty() );
  assert( !isOpen() );

  mImpl->setFilePath(filePath);
}

const std::string & CsvFileReader::filePath() const noexcept
{
  return mImpl->filePath();
}

void CsvFileReader::setCsvSettings(const CsvParserSettings & settings) noexcept
{
  assert( settings.isValid() );
  assert( !isOpen() );

  mImpl->setCsvSettings(settings);
}

const CsvParserSettings & CsvFileReader::csvSettings() const noexcept
{
  return mImpl->csvSettings();
}

void CsvFileReader::open()
{
  assert( !filePath().empty() );

  mImpl->open();
}

bool CsvFileReader::isOpen() const
{
  return mImpl->isOpen();
}

bool CsvFileReader::atEnd() const noexcept
{
  assert( isOpen() );

  return mImpl->atEnd();
}

std::vector<std::string> CsvFileReader::readLine() const
{
  assert( isOpen() );

  return mImpl->readLine< std::vector<std::string> >();
}

std::vector< std::vector<std::string> > CsvFileReader::readAll() const
{
  assert( isOpen() );

  return mImpl->readAll< std::vector< std::vector<std::string> > >();
}

void CsvFileReader::close()
{
  mImpl->close();
}

}} // namespace Mdt{ namespace PlainText{
