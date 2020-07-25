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
#include "TextFileUtils.h"
#include <QTextStream>
#include <QFileInfo>
#include <QFile>
#include <QDebug>
#include <cassert>

namespace Mdt{ namespace PlainText{ namespace TestLib{

bool fileExists(const QString & filePath)
{
  return QFileInfo::exists(filePath);
}

bool writeTextFileUtf8(QFile & file, const QString & content)
{
  assert( file.isOpen() );
  assert( file.isWritable() );

  QTextStream out(&file);
  out.setCodec("UTF-8");
  out << content;

  return true;
}

bool writeTextFileUtf8(const QString & filePath, const QString & content)
{
  assert( !filePath.isEmpty() );

  QFile file(filePath);
  if( !file.open(QIODevice::WriteOnly | QIODevice::Text) ){
    qWarning() << "Mdt::PlainText::TestLib::writeTextFileUtf8(): open file '" << filePath << "' failed: " << file.errorString();
    return false;
  }
  if( !writeTextFileUtf8(file, content) ){
    return false;
  }
  file.close();

  return true;
}

QString readTextFileUtf8(const QString & filePath)
{
  assert( !filePath.isEmpty() );

  QString content;

  QFile file(filePath);
  if( !file.open(QIODevice::ReadOnly | QIODevice::Text) ){
    qWarning() << "Mdt::PlainText::TestLib::readTextFileUtf8(): open file '" << filePath << "' failed: " << file.errorString();
    return content;
  }

  QTextStream in(&file);
  in.setCodec("UTF-8");
  while (!in.atEnd()) {
    QString line = in.readLine();
    content += line;
  }

  return content;
}

}}} // namespace Mdt{ namespace PlainText{ namespace TestLib{
