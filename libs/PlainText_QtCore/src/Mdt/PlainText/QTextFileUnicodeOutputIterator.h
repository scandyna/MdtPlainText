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
#ifndef MDT_PLAIN_TEXT_QTEXT_FILE_UNICODE_OUTPUT_ITERATOR_H
#define MDT_PLAIN_TEXT_QTEXT_FILE_UNICODE_OUTPUT_ITERATOR_H

#include "QTextFileOutputIterator.h"
#include "QTextCodecNotFoundError.h"
#include "QFileWriteError.h"
#include "mdt_plaintext_qtcore_export.h"
#include <QFileDevice>
#include <QByteArray>
#include <QChar>
#include <iterator>
#include <cstdint>
#include <cassert>

namespace Mdt{ namespace PlainText{

  /*! \brief A output iterator that appends unicode code points to a file
   *
   * This iterator is based on QTextFileOutputIterator,
   * but exposes unicode points as uint32_t value type, instead of UTF-16 QChar.
   *
   * Example:
   * \code
   * using Mdt::PlainText::QTextFileUnicodeOutputIterator;
   *
   * QFile file("out.txt");
   * if( !file.open(QIODevice::WriteOnly | QIODevice::Text) )
   * {
   *   // Error handling
   * }
   * QTextFileUnicodeOutputIterator it(file, "UTF-8");
   * std::fill_n(it, 5, U'𝛀');
   * \endcode
   */
  class MDT_PLAINTEXT_QTCORE_EXPORT QTextFileUnicodeOutputIterator
  {
    public:

    /*! \brief STL iterator difference_type
     */
    using difference_type = void;

    /*! \brief STL iterator value_type
     */
    using value_type = void;

    /*! \brief STL iterator pointer
     */
    using pointer = void;

    /*! \brief STL iterator reference
     */
    using reference = void;

    /*! \brief STL iterator iterator_category
     */
    using iterator_category = std::output_iterator_tag;

    /*! \brief Construct a null iterator
     */
    QTextFileUnicodeOutputIterator() noexcept = default;

    /*! \brief Construct a iterator that acts on a file
     *
     * \pre \a file must be open with a writable mode
     * \exception QTextCodecNotFoundError
     */
    explicit QTextFileUnicodeOutputIterator(QFileDevice & file, const QByteArray & fileEncoding)
     : mIt(file, fileEncoding)
    {
      assert( file.isOpen() );
    }

    /*! \brief Append \a codePoint to the string
     */
    QTextFileUnicodeOutputIterator & operator=(uint32_t codePoint)
    {
      if( QChar::requiresSurrogates(codePoint) ){
        mIt = QChar::highSurrogate(codePoint);
        mIt = QChar::lowSurrogate(codePoint);
      }else{
        mIt = QChar(codePoint);
      }

      return *this;
    }

    /*! \brief Does nothing and return *this
     *
     * Provided to satisfy the requirements of LegacyOutputIterator.
     *
     * It returns the iterator itself, which makes it possible to use code such as
     * \code
     * *iter = value
     * \endcode
     * to output (insert) the value into the underlying file. 
     */
    constexpr QTextFileUnicodeOutputIterator & operator*()
    {
      return *this;
    }

    /*! \brief Does nothing and return *this
     *
     * Provided to satisfy the requirements of LegacyOutputIterator.
     *
     * It returns the iterator itself, which makes it possible to use code such as
     * \code
     * *++iter = value
     * \endcode
     * to output (insert) the value into the underlying file. 
     */
    constexpr QTextFileUnicodeOutputIterator & operator++()
    {
      return *this;
    }

    /*! \brief Does nothing and return *this
     *
     * Provided to satisfy the requirements of LegacyOutputIterator.
     *
     * It returns the iterator itself, which makes it possible to use code such as
     * \code
     * *iter++ = value
     * \endcode
     * to output (insert) the value into the underlying file. 
     */
    constexpr QTextFileUnicodeOutputIterator & operator++(int)
    {
      return *this;
    }

   private:

    QTextFileOutputIterator mIt;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_QTEXT_FILE_UNICODE_OUTPUT_ITERATOR_H
