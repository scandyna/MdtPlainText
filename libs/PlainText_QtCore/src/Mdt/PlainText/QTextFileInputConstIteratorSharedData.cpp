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
#include "QTextFileInputConstIteratorSharedData.h"
#include "QFileReadError.h"
#include <QTextCodec>

namespace Mdt{ namespace PlainText{

QTextFileInputConstIteratorSharedData::QTextFileInputConstIteratorSharedData(QFileDevice *file, const QByteArray & fileEncoding, int rawBufferCapacity)
  : QObject(nullptr),
    mRawDataBuffer(rawBufferCapacity),
    mFile(file)
{
  Q_ASSERT( file != nullptr );
  Q_ASSERT( file->isOpen() );
  Q_ASSERT( fileOpenModeIsReadable(*file) );
  Q_ASSERT( rawBufferCapacity > 0 );

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

  mDecoder.reset( codec->makeDecoder() );
  Q_ASSERT( mDecoder.get() != nullptr );

  readMore();
  mCurrentPos = mUnicodeBuffer.cbegin();
}

qint64 QTextFileInputConstIteratorSharedData::readFromFile()
{
  Q_ASSERT(mFile);
  Q_ASSERT(mRawDataBuffer.capacity() > 0);
  Q_ASSERT( mRawDataBuffer.empty() );

  const qint64 n = mFile->read( mRawDataBuffer.data(), mRawDataBuffer.capacity() );
  if( n < 0 ){
    const QString what = tr("Reading from file '%1' failed: '%2'")
                         .arg( mFile->fileName(), mFile->errorString() );
    throw QFileReadError(what);
  }

  return n;
}

void QTextFileInputConstIteratorSharedData::decodeToUnicodeBuffer(qint64 rawCharsCount)
{
  Q_ASSERT( mUnicodeBuffer.isEmpty() );
  Q_ASSERT( mDecoder.get() != nullptr );

  mDecoder->toUnicode(&mUnicodeBuffer, mRawDataBuffer.data(), rawCharsCount);
  mCurrentPos = mUnicodeBuffer.cbegin();
}

void QTextFileInputConstIteratorSharedData::readMore()
{
  while( mUnicodeBuffer.isEmpty() ){
    const auto n = readFromFile();
    if( n < 1 ){
      return;
    }
    decodeToUnicodeBuffer(n);
  }
}

}} // namespace Mdt{ namespace PlainText{
