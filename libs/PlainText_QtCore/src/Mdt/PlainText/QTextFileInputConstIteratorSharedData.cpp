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
#include <QCoreApplication>

namespace Mdt{ namespace PlainText{

namespace Impl{

  int readFromFile(QIODevice & file, const QString & fileName, std::vector<char> & rawDataBuffer)
  {
    assert( rawDataBuffer.empty() );
    assert( rawDataBuffer.capacity() > 0 );

    if( !file.isOpen() ){
      const QString what = QCoreApplication::translate("QTextFileInputConstIteratorSharedData", "Reading from file '%1' because it was closed")
                          .arg(fileName);
      throw QFileReadError(what);
    }

    rawDataBuffer.resize( rawDataBuffer.capacity() );
    const int n = file.read( rawDataBuffer.data(), rawDataBuffer.size() );
    if(n < 0){
      const QString what = QCoreApplication::translate("QTextFileInputConstIteratorSharedData", "Reading from file '%1' failed: '%2'")
                          .arg( fileName, file.errorString() );
      throw QFileReadError(what);
    }
    assert( static_cast<std::size_t>(n) <= rawDataBuffer.capacity() );
    rawDataBuffer.resize(n);

    return n;
  }

  void decodeToUnicodeBuffer(QTextDecoder & decoder,  const std::vector<char> & rawDataBuffer, QString & unicodeBuffer)
  {
    assert( !rawDataBuffer.empty() );
    assert( unicodeBuffer.isEmpty() );

    decoder.toUnicode( &unicodeBuffer, rawDataBuffer.data(), rawDataBuffer.size() );
  }

  bool readFromFileAndDecode(QIODevice & file, const QString & fileName, QTextDecoder & decoder, std::vector<char> & rawDataBuffer, QString & unicodeBuffer)
  {
    assert( rawDataBuffer.empty() );
    assert( unicodeBuffer.isEmpty() );

    while( unicodeBuffer.isEmpty() ){
      const int n = readFromFile(file, fileName, rawDataBuffer);
      if(n < 1){
        return false;
      }
      decodeToUnicodeBuffer(decoder, rawDataBuffer, unicodeBuffer);
      rawDataBuffer.clear();
    }

    return true;
  }

} // namespace Impl{


QTextFileInputConstIteratorSharedData::QTextFileInputConstIteratorSharedData(QFileDevice & file, const QByteArray & fileEncoding, int rawBufferCapacity)
  : QObject(nullptr),
    mFile(&file)
{
  assert( file.isOpen() );
  assert( fileOpenModeIsReadable(file) );
  assert( rawBufferCapacity > 0 );

  mRawDataBuffer.reserve(rawBufferCapacity);

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
  assert( mDecoder.get() != nullptr );

  readMore();
  mCurrentPos = mUnicodeBuffer.cbegin();
}

void QTextFileInputConstIteratorSharedData::readMore()
{
  assert(mFile);
  assert( mDecoder.get() != nullptr );
  assert( mRawDataBuffer.empty() );
  assert( mUnicodeBuffer.isEmpty() );

  Impl::readFromFileAndDecode(*mFile, mFile->fileName(), *mDecoder, mRawDataBuffer, mUnicodeBuffer);
}

}} // namespace Mdt{ namespace PlainText{
