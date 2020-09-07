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
#ifndef MDT_PLAIN_TEXT_QTEXT_FILE_UNICODE_INPUT_CONST_ITERATOR_H
#define MDT_PLAIN_TEXT_QTEXT_FILE_UNICODE_INPUT_CONST_ITERATOR_H

#include "QTextFileInputConstIterator.h"
#include "mdt_plaintext_qtcore_export.h"
#include <QFileDevice>
#include <QByteArray>
#include <QChar>
#include <boost/iterator/iterator_facade.hpp>
#include <cstdint>
#include <cassert>

namespace Mdt{ namespace PlainText{

  namespace Impl{

    /*! \internal
     *
     * \note We act on a input iterator (QTextFileInputConstIterator),
     * which does not provide the multi-pass garantie.
     * Because get the value at current position multiple times,
     * we have to cache it.
     */
    struct QTextFileUnicodeInputConstIteratorImpl
    {
      uint32_t codePoint = 0;
      QChar currentCodeUint;
      QTextFileInputConstIterator mIterator;

      QTextFileUnicodeInputConstIteratorImpl() noexcept = default;

      QTextFileUnicodeInputConstIteratorImpl(QFileDevice & file, const QByteArray & fileEncoding)
       : mIterator(file, fileEncoding)
      {
        assert( file.isOpen() );

        if( isDereferencable() ){
          currentCodeUint = *mIterator;
        }
      }

      QTextFileUnicodeInputConstIteratorImpl(const QTextFileUnicodeInputConstIteratorImpl & other) noexcept = default;

      QTextFileUnicodeInputConstIteratorImpl & operator=(const QTextFileUnicodeInputConstIteratorImpl & other) noexcept = default;

      QTextFileUnicodeInputConstIteratorImpl(QTextFileUnicodeInputConstIteratorImpl && other) noexcept = default;

      QTextFileUnicodeInputConstIteratorImpl & operator=(QTextFileUnicodeInputConstIteratorImpl && other) noexcept = default;

      bool atEnd() const noexcept
      {
        return mIterator.isEof();
      }

      bool isDereferencable() const noexcept
      {
        return !mIterator.isEof();
      }

      void increment()
      {
        assert( !atEnd() );

        ++mIterator;
        if( isDereferencable() ){
          currentCodeUint = *mIterator;
          if( currentCodeUint.isLowSurrogate() ){
            assert( !atEnd() );
            ++mIterator;
            if( isDereferencable() ){
              currentCodeUint = *mIterator;
            }
          }
        }
      }

      void extractCodePoint()
      {
        assert( isDereferencable() );

        if( currentCodeUint.isHighSurrogate() ){
          assert( !atEnd() );
          ++mIterator;
          codePoint = QChar::surrogateToUcs4( currentCodeUint, *mIterator );
        }else{
          assert( !currentCodeUint.isSurrogate() );
          codePoint = currentCodeUint.unicode();
        }
      }
    };

  } // namespace Impl{

  /*! \brief Input iterator that reads file and provide unicode support
   *
   * This iterator is based on QTextFileInputConstIterator,
   * but exposes unicode points as uint32_t value type, instead of UTF-16 QChar.
   *
   * To use this iterator with boost Spirit,
   * [the multi pass iterator](https://www.boost.org/doc/libs/1_73_0/libs/spirit/doc/html/spirit/support/multi_pass.html)
   * should be used.
   *
   * \note Because this iterator has to be copiable,
   * it does not use the multi pass iterator internally,
   * avoiding to copy buffered data every time.
   */
  class MDT_PLAINTEXT_QTCORE_EXPORT QTextFileUnicodeInputConstIterator : public boost::iterator_facade<
      QTextFileUnicodeInputConstIterator,     // Derived
      uint32_t,                               // Value
      boost::single_pass_traversal_tag,       // CategoryOrTraversal
      uint32_t                                // Reference
    >
  {
   public:

    /*! \brief Construct a end-of-file iterator
     */
    QTextFileUnicodeInputConstIterator() noexcept = default;

    /*! \brief Construct a iterator that acts on a file
     *
     * Will read some data from \a file until a unicode point could be decoded.
     * If \a file is at end, or not enough data is available to get a unicode point,
     * this iterator falls back to a end-of-file iterator.
     *
     * \pre \a file must be open with a readable mode
     * \exception QTextCodecNotFoundError
     * \exception QFileReadError
     */
    QTextFileUnicodeInputConstIterator(QFileDevice & file, const QByteArray & fileEncoding)
     : mImpl(file, fileEncoding)
    {
      assert( file.isOpen() );

      extractCodePointIfDereferencable();
    }

    /*! \brief Copy construct a iterator from \a other
     */
    QTextFileUnicodeInputConstIterator(const QTextFileUnicodeInputConstIterator & other) noexcept = default;

   private:

    friend class boost::iterator_core_access;

    void increment()
    {
      mImpl.increment();
      extractCodePointIfDereferencable();
    }

    bool equal(const QTextFileUnicodeInputConstIterator & other) const
    {
      return mImpl.mIterator == other.mImpl.mIterator;
    }

    uint32_t dereference() const
    {
      return mImpl.codePoint;
    }

    void extractCodePointIfDereferencable()
    {
      if( mImpl.isDereferencable() ){
        mImpl.extractCodePoint();
      }
    }

    Impl::QTextFileUnicodeInputConstIteratorImpl mImpl;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_QTEXT_FILE_UNICODE_INPUT_CONST_ITERATOR_H
