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
#include "QTextFileOutputIteratorImpl.h"
#include <QTextCodec>
#include <QString>

namespace Mdt{ namespace PlainText{

QTextFileOutputIteratorImpl::QTextFileOutputIteratorImpl(QFileDevice & file, const QByteArray & fileEncoding)
  : QObject(nullptr),
    mFile(&file)
{
  assert( file.isOpen() );
  assert( fileOpenModeIsWritable(file) );

  /*
   * Find a codec for requested encoding
   * Note: we not have to manage codec lifetime,
   *       see QTextCodec::~QTextCodec()
   */
  auto *codec = QTextCodec::codecForName(fileEncoding);
  if(codec == nullptr){
    const QString what = tr("Could not find a codec for requested encoding '%1'").arg( QString::fromLatin1(fileEncoding) );
    throw QTextCodecNotFoundError(what);
  }

  mEncoder.reset( codec->makeEncoder() );
  assert( mEncoder.get() != nullptr );

}

void QTextFileOutputIteratorImpl::put(const QChar & c)
{
  assert(mFile);
  assert( mEncoder.get() != nullptr );

  const QByteArray ba = mEncoder->fromUnicode(&c, 1);
  const auto written = mFile->write(ba);

  if(written < 0){
    const QString what = tr("Writing to file '%1' failed: '%2'")
                         .arg( mFile->fileName(), mFile->errorString() );
    throw QFileWriteError(what);
  }
}

}} // namespace Mdt{ namespace PlainText{
