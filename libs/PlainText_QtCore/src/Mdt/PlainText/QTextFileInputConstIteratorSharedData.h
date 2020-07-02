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
#ifndef MDT_PLAIN_TEXT_QTEXT_FILE_INPUT_CONST_ITERATOR_SHARED_DATA_H
#define MDT_PLAIN_TEXT_QTEXT_FILE_INPUT_CONST_ITERATOR_SHARED_DATA_H

#include "QTextCodecNotFoundError.h"
#include "mdt_plaintext_qtcore_export.h"
#include <QObject>
#include <QFileDevice>
#include <QByteArray>
#include <QString>
#include <QTextDecoder>
#include <QPointer>
#include <memory>
#include <vector>

namespace Mdt{ namespace PlainText{

  /*! \internal Implementation part for QTextFileInputConstIterator
   */
  class MDT_PLAINTEXT_QTCORE_EXPORT QTextFileInputConstIteratorSharedData : public QObject
  {
    Q_OBJECT

   public:

    /*! \brief Constructor
     *
     * Will read some data from \a file until a unicode character could be decoded.
     * If \a file is at end, or not enough data is available to get a unicode character,
     * atEnd() will return true.
     *
     * \pre \a file must be a valid pointer
     * \pre \a file must be open with a readable mode
     * \exception QTextCodecNotFoundError
     * \exception QFileReadError
     */
    explicit QTextFileInputConstIteratorSharedData(QFileDevice *file, const QByteArray & fileEncoding, int rawBufferCapacity = 1024);

    QTextFileInputConstIteratorSharedData(const QTextFileInputConstIteratorSharedData &) = delete;
    QTextFileInputConstIteratorSharedData & operator=(const QTextFileInputConstIteratorSharedData &) = delete;

    QTextFileInputConstIteratorSharedData(const QTextFileInputConstIteratorSharedData &&) = delete;
    QTextFileInputConstIteratorSharedData & operator=(QTextFileInputConstIteratorSharedData &&) = delete;

    /*! \brief Check if end was reached
     *
     * Returns true once we reached the en of the file
     * and no more unicode char is available in the internal unicode buffer.
     */
    bool atEnd() const
    {
      Q_ASSERT(mFile);

      return atEndOfUnicodeBuffer() && mFile->atEnd();
    }

    /*! \brief Advance by one unicode char in the buffer
     *
     * If internal unicode buffer has data available,
     *  current position is simply incremented by 1.
     *  If no more data is available any more,
     *  a chunk is readen frome file.
     *
     * \pre This function must not be called after atEnd() returns true.
     * \exception QFileReadError
     * \sa lastError()
     * \sa get()
     */
    void advance()
    {
      Q_ASSERT( !atEnd() );
      Q_ASSERT(mFile);
      Q_ASSERT( mDecoder.get() != nullptr );

      ++mCurrentPos;

      if( atEndOfUnicodeBuffer() ){
        mUnicodeBuffer.clear();
        readMore();
        mCurrentPos = mUnicodeBuffer.cbegin();
      }
    }

    /*! \brief Get current char in unicode buffer
     *
     * Does nothing else than return the char
     *  referenced by current position.
     *  Calling this function multiple
     *  times also returns allways the same char.
     *
     * \pre This function must not be called after atEnd() returns true.
     */
    const QChar & get() const noexcept
    {
      Q_ASSERT( !atEnd() );

      return *mCurrentPos;
    }

    static
    bool fileOpenModeIsReadable(const QFileDevice & file)
    {
      const auto flags = file.openMode();

      if( flags.testFlag(QIODevice::ReadOnly) ){
        return true;
      }

      return false;
    }

   private:

    bool atEndOfUnicodeBuffer() const noexcept
    {
      return mCurrentPos == mUnicodeBuffer.cend();
    }

    qint64 readFromFile();
    void decodeToUnicodeBuffer(qint64 rawCharsCount);
    void readMore();

    QString::const_iterator mCurrentPos;
    QString mUnicodeBuffer;
    std::vector<char> mRawDataBuffer;
    std::unique_ptr<QTextDecoder> mDecoder;
    QPointer<QFileDevice> mFile;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_QTEXT_FILE_INPUT_CONST_ITERATOR_SHARED_DATA_H
