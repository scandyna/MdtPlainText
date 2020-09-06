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
#ifndef MDT_PLAIN_TEXT_QTEXT_FILE_OUTPUT_ITERATOR_H
#define MDT_PLAIN_TEXT_QTEXT_FILE_OUTPUT_ITERATOR_H

#include "QTextFileOutputIteratorImpl.h"
#include "QTextCodecNotFoundError.h"
#include "QFileWriteError.h"
#include "mdt_plaintext_qtcore_export.h"
#include <QFileDevice>
#include <QByteArray>
#include <QChar>
#include <iterator>
#include <memory>
#include <cassert>

namespace Mdt{ namespace PlainText{

  /*! \brief Output iterator that writes file and provide some unicode support (UTF-16)
   *
   * Internally, QTextEncoder is used to provide unicode support.
   *
   * If you need to add unicode code points (not UTF-16 code units) to a file,
   * considere using QTextFileUnicodeOutputIterator.
   *
   * \sa QTextFileUnicodeOutputIterator
   */
  class MDT_PLAINTEXT_QTCORE_EXPORT QTextFileOutputIterator
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
    QTextFileOutputIterator() noexcept = default;

    /*! \brief Construct a iterator that acts on a file
     *
     * \pre \a file must be a valid pointer
     * \pre \a file must be open with a writable mode
     * \exception QTextCodecNotFoundError
     *
     * \todo Should take file by reference, see https://en.cppreference.com/w/cpp/iterator/ostreambuf_iterator/ostreambuf_iterator
     */
    explicit QTextFileOutputIterator(QFileDevice *file, const QByteArray & fileEncoding)
     : mImpl( std::make_shared<QTextFileOutputIteratorImpl>(file, fileEncoding) )
    {
      assert( file != nullptr );
      assert( file->isOpen() );
      assert( fileOpenModeIsWritable(*file) );
    }

    /*! \brief Append a code unit to the file
     *
     * \exception QFileWriteError
     */
    QTextFileOutputIterator & operator=(QChar c)
    {
      assert( mImpl.get() != nullptr );

      mImpl->put(c);

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
    constexpr QTextFileOutputIterator & operator*()
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
    constexpr QTextFileOutputIterator & operator++()
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
    constexpr QTextFileOutputIterator & operator++(int)
    {
      return *this;
    }

   private:

    static
    bool fileOpenModeIsWritable(const QFileDevice & file)
    {
      return QTextFileOutputIteratorImpl::fileOpenModeIsWritable(file);
    }

    std::shared_ptr<QTextFileOutputIteratorImpl> mImpl;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_QTEXT_FILE_OUTPUT_ITERATOR_H
