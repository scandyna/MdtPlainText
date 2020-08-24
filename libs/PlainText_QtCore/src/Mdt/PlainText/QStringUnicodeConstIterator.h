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
#ifndef MDT_PLAIN_TEXT_QSTRING_CONST_ITERATOR_H
#define MDT_PLAIN_TEXT_QSTRING_CONST_ITERATOR_H

#include "mdt_plaintext_qtcore_export.h"
#include <QString>
#include <QChar>
#include <boost/iterator/iterator_facade.hpp>
#include <cstdint>
#include <cassert>

namespace Mdt{ namespace PlainText{

  namespace Impl{

    /*! \internal
     */
    struct QStringUnicodeConstIteratorData
    {
      uint32_t value = 0;
      QString::const_iterator begin = nullptr;
      QString::const_iterator position = nullptr;
      QString::const_iterator end = nullptr;

      constexpr
      QStringUnicodeConstIteratorData() noexcept = default;

      constexpr
      QStringUnicodeConstIteratorData(QString::const_iterator begin, QString::const_iterator pos, QString::const_iterator end) noexcept
       : begin(begin),
         position(pos),
         end(end)
      {
      }

      constexpr
      QStringUnicodeConstIteratorData(const QStringUnicodeConstIteratorData & other) noexcept = default;

      constexpr
      QStringUnicodeConstIteratorData & operator=(const QStringUnicodeConstIteratorData & other) noexcept = default;

      constexpr
      QStringUnicodeConstIteratorData(QStringUnicodeConstIteratorData && other) noexcept = default;

      constexpr
      QStringUnicodeConstIteratorData & operator=(QStringUnicodeConstIteratorData && other) noexcept = default;

      constexpr
      bool hasNext() const noexcept
      {
        return position < (end - 1);
      }

      constexpr
      bool hasPrevious() const noexcept
      {
        return position > begin;
      }

      constexpr
      bool atEnd() const noexcept
      {
        return position == end;
      }

      constexpr
      bool atBegin() const noexcept
      {
        return position == begin;
      }

      constexpr
      bool isDereferencable() const noexcept
      {
        if( position == nullptr ){
          return false;
        }
        assert( begin != nullptr );
        assert( end != nullptr );

        return position != end;
      }

      void increment()
      {
        assert( !atEnd() );

        ++position;
        if( isDereferencable() ){
          if( position->isLowSurrogate() ){
            assert( !atEnd() );
            ++position;
          }
        }
      }

      void decrement()
      {
        assert( !atBegin() );

        --position;
        if( isDereferencable() ){
          if( position->isLowSurrogate() ){
            assert( !atBegin() );
            --position;
          }
        }
      }

      void extractCodePoint()
      {
        assert( isDereferencable() );

        if( position->isHighSurrogate() ){
          assert( hasNext() );
          value = QChar::surrogateToUcs4( *position, *(position+1) );
        }else{
          assert( !position->isSurrogate() );
          value = position->unicode();
        }
      }
    };

  } // namespace Impl{

  /*! \brief QString unicode const iterator
   *
   * QString::const_iterator is a pointer to a QChar,
   * which gives access to each code unit in a QString,
   * not the code point.
   *
   * QStringUnicodeConstIterator travels code points in a QString,
   * and return it as a 32bit unicode value.
   *
   * \code
   * using Mdt::PlainText::QStringUnicodeConstIterator;
   *
   * QStringUnicodeConstIterator first( str.cbegin(), str.cend() );
   * QStringUnicodeConstIterator last( str.cend(), str.cend() );
   * \endcode
   *
   * Because it has to check each UTF-16 code unit to know
   * if it is a surrogate pair, this iterator cannot be random acces,
   * so it is a [bidirectional iterator](https://en.cppreference.com/w/cpp/named_req/BidirectionalIterator).
   *
   * \note At each point, this iterator must know if it can be dereferenced
   * to check if the current position is part of a surrogate pair.
   * This is why it requires to know the end of the string.
   *
   * This code is inspired from a private class available in Qt:
   * \sa https://www.kdab.com/a-little-hidden-gem-qstringiterator
   *
   * \sa https://stackoverflow.com/questions/57461106/how-can-i-use-boostspirit-x3-in-conjunction-with-qstring
   */
  class MDT_PLAINTEXT_QTCORE_EXPORT QStringUnicodeConstIterator : public boost::iterator_facade<
      QStringUnicodeConstIterator,        // Derived
      const uint32_t,                     // Value
      boost::bidirectional_traversal_tag, // CategoryOrTraversal
      const uint32_t &,                   // Reference, see dereference()
      ptrdiff_t                           // Difference
    >
  {
   public:

    /*! \brief Default constructor
     */
    QStringUnicodeConstIterator() noexcept = default;

    /*! \brief Construct a iterator that points to \a it
     *
     * \note Surprisingly, the \a end iterator is required here.
     *  This is because the codepoint value (uint32_t) can be a composition
     *  of 2 UTF16 (QChar) codepoints.
     */
    QStringUnicodeConstIterator(QString::const_iterator it, QString::const_iterator end)
     : mData(it, it, end)
    {
      extractCodePointIfDereferencable();
    }

    /*! \brief Constrcut a const iterator from the non const iterator \a it
     *
     * \note Surprisingly, the \a end iterator is required here.
     *  This is because the codepoint value (uint32_t) can be a composition
     *  of 2 UTF16 (QChar) codepoints.
     */
    QStringUnicodeConstIterator(QString::iterator it, QString::iterator end)
     : mData(it, it, end)
    {
      extractCodePointIfDereferencable();
    }

    /*! \brief Copy construct a iterator from \a other
     */
    QStringUnicodeConstIterator(const QStringUnicodeConstIterator & other) noexcept = default;

  private:

    friend class boost::iterator_core_access;

    bool equal(const QStringUnicodeConstIterator & other) const
    {
      return mData.position == other.mData.position;
    }

    void increment()
    {
      mData.increment();
      extractCodePointIfDereferencable();
    }

    void decrement()
    {
      mData.decrement();
      extractCodePointIfDereferencable();
    }

    void extractCodePointIfDereferencable()
    {
      if( mData.isDereferencable() ){
        mData.extractCodePoint();
      }
    }

    /*! \internal
     *
     * \note To be recognized as a bidirectional iterator,
     * the reference type MUST be a reference.
     * If not doing so, boost::iterator_facade will
     * tell that this iterator is a input iterator (!)
     *
     * \sa https://github.com/boostorg/iterator/issues/47
     */
    const uint32_t & dereference() const noexcept
    {
      return mData.value;
    }

    Impl::QStringUnicodeConstIteratorData mData;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_QSTRING_CONST_ITERATOR_H
