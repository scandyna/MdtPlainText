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
#include "Mdt/PlainText/TestLib/ContainerCompare.h"
#include "Mdt/PlainText/TestLib/CsvTestFiles.h"
#include "Mdt/PlainText/QCsvFileReader"
#include <QString>
#include <QByteArray>
#include <QFileInfo>

using namespace Mdt::PlainText;
using namespace Mdt::PlainText::TestLib;

void setTestFilePathToReader(const char *testFileName, QCsvFileReader & reader)
{
  const QString filePath = Mdt::PlainText::TestLib::csvTestFilePath(testFileName);
  Q_ASSERT( QFileInfo::exists(filePath) );

  reader.setFilePath(filePath);
}
