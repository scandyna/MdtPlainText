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
#ifndef MDT_PLAIN_TEXT_QTEXT_FILE_INPUT_CONST_ITERATOR_H
#define MDT_PLAIN_TEXT_QTEXT_FILE_INPUT_CONST_ITERATOR_H

#include "QTextCodecNotFoundError.h"
#include "QFileReadError.h"
#include "QTextFileInputConstIteratorSharedData.h"
#include "mdt_plaintext_qtcore_export.h"
#include <QFileDevice>
#include <QByteArray>
#include <QChar>
#include <QFlags>
#include <boost/iterator/iterator_facade.hpp>
#include <memory>

namespace Mdt{ namespace PlainText{

  /*! \brief Input iterator that reads file and provide unicode support
   *
   * QTextFileInputConstIterator is a single-pass input iterator
   * that reads a file.
   *
   * Internally, QTextDecoder is used to provide unicode support.
   *
   * Example:
   * \code
   * using Mdt::PlainText::QTextFileInputConstIterator;
   *
   * QTextFile file("file.txt");
   * if( !file.open(QIODevice::ReadOnly | QIODevice::Text) ){
   *   // Error handling
   * }
   *
   * QTextFileInputConstIterator first(&file, "UTF-8");
   * QTextFileInputConstIterator last;
   * while(first != last){
   *   qDebug() << "*first: " << *first;
   *   ++first;
   * }
   * \endcode
   */
  class MDT_PLAINTEXT_QTCORE_EXPORT QTextFileInputConstIterator : public boost::iterator_facade<
      QTextFileInputConstIterator,      // Derived
      const QChar,                      // Value
      boost::single_pass_traversal_tag  // CategoryOrTraversal
    >
  {
   public:

     /*! \brief Construct a end-of-file iterator
      */
     QTextFileInputConstIterator() noexcept = default;

     /*! \brief Construct a iterator that acts on a file
      *
      * Will read some data from \a file until a unicode character could be decoded.
      * If \a file is at end, or not enough data is available to get a unicode character,
      * this iterator falls back to a end-of-file iterator.
      *
      * \pre \a file must be a valid pointer
      * \pre \a file must be open with a readable mode
      * \exception QTextCodecNotFoundError
      * \exception QFileReadError
      */
     QTextFileInputConstIterator(QFileDevice *file, const QByteArray & fileEncoding)
      : mImpl( std::make_shared<QTextFileInputConstIteratorSharedData>(file, fileEncoding) )
     {
       Q_ASSERT( file != nullptr );
       Q_ASSERT( file->isOpen() );
       Q_ASSERT( fileOpenModeIsReadable(*file) );
     }

    /*! \brief Copy construct a iterator from \a other
     */
    QTextFileInputConstIterator(const QTextFileInputConstIterator & other) noexcept = default;

     /*! \brief Check if this iterator is a end-of-file iterator
      */
     bool isEof() const noexcept
     {
       if( !mImpl ){
         return true;
       }
       Q_ASSERT( mImpl.get() != nullptr );

       return mImpl->atEnd();
     }

   private:

    friend class boost::iterator_core_access;

    void increment()
    {
      Q_ASSERT( !isEof() );
      Q_ASSERT( mImpl.get() != nullptr );

      mImpl->advance();
    }

    bool equal(const QTextFileInputConstIterator & other) const
    {
      return other.isEof() == isEof();
    }

    const QChar & dereference() const noexcept
    {
      Q_ASSERT( !isEof() );
      Q_ASSERT( mImpl.get() != nullptr );

      return mImpl->get();
    }

    static
    bool fileOpenModeIsReadable(const QFileDevice & file)
    {
      return QTextFileInputConstIteratorSharedData::fileOpenModeIsReadable(file);
    }

    std::shared_ptr<QTextFileInputConstIteratorSharedData> mImpl;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_QTEXT_FILE_INPUT_CONST_ITERATOR_H
