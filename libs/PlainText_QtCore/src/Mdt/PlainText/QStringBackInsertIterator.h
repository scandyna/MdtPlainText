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
#ifndef MDT_PLAIN_TEXT_QSTRING_BACK_INSERT_ITERATOR_H
#define MDT_PLAIN_TEXT_QSTRING_BACK_INSERT_ITERATOR_H

#include "Mdt/PlainText/Impl/AddCodePointToQString.h"
#include "mdt_plaintext_qtcore_export.h"
#include <QString>
#include <cstdint>
#include <iterator>
#include <cassert>

namespace Mdt{ namespace PlainText{

  /*! \brief A output iterator that appends unicode code points to a QString
   *
   * QString::iterator is a pointer to a QChar,
   * which gives access to each code unit in a QString,
   * not the code point.
   *
   * Example:
   * \code
   * using Mdt::PlainText::QStringBackInsertIterator;
   *
   * QString str;
   * std::fill_n( QStringBackInsertIterator(str), 5, U'𝛀' );
   * \endcode
   */
  class MDT_PLAINTEXT_QTCORE_EXPORT QStringBackInsertIterator
  {
   public:

    using iterator_category = std::output_iterator_tag;
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;
    using container_type = QString;

    /*! \brief Construct a back insert iterator to act on \a str
     */
    explicit QStringBackInsertIterator(QString & str)
     : mString(str)
    {
    }

    /*! \brief Append \a codePoint to the string
     */
    QStringBackInsertIterator & operator=(uint32_t codePoint)
    {
      Impl::addCodePointToQString(codePoint, mString);

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
     * to output (insert) the value into the underlying string. 
     */
    constexpr QStringBackInsertIterator & operator*()
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
     * to output (insert) the value into the underlying string. 
     */
    constexpr QStringBackInsertIterator & operator++()
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
     * to output (insert) the value into the underlying string. 
     */
    constexpr QStringBackInsertIterator & operator++(int)
    {
      return *this;
    }

   private:

    QString & mString;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_QSTRING_BACK_INSERT_ITERATOR_H
