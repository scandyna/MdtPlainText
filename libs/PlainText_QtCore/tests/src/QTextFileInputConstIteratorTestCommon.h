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
#include "Mdt/PlainText/QTextFileInputConstIterator.h"
#include "Mdt/PlainText/TestLib/TextFileUtils.h"
#include <QTemporaryFile>
#include <QLatin1String>
#include <QLatin1Char>
#include <type_traits>
#include <algorithm>

using namespace Mdt::PlainText;

bool openTextFileReadOnly(QFile & file)
{
  return file.open(QIODevice::ReadOnly | QIODevice::Text);
}

bool writeTextFile(QFile & file, const QString & content)
{
  return Mdt::PlainText::TestLib::writeTextFileUtf8(file, content);
}
