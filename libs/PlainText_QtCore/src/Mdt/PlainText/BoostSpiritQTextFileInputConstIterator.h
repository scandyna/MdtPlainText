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
#ifndef MDT_PLAIN_TEXT_BOOST_SPIRIT_QTEXT_FILE_INPUT_CONST_ITERATOR_H
#define MDT_PLAIN_TEXT_BOOST_SPIRIT_QTEXT_FILE_INPUT_CONST_ITERATOR_H

#include "QTextFileInputConstIterator.h"
#include "mdt_plaintext_qtcore_export.h"
#include <QFileDevice>
#include <QByteArray>
#include <boost/iterator/iterator_adaptor.hpp>

namespace Mdt{ namespace PlainText{

  /*! \brief Input iterator that reads file and provide unicode support
   *
   * This iterator is based on QTextFileInputConstIterator,
   * but exposes uint32_t as value type, instead of QChar.
   *
   * To use this iterator with boost Spirit,
   * [the multi pass iterator](https://www.boost.org/doc/libs/1_73_0/libs/spirit/doc/html/spirit/support/multi_pass.html)
   * should be used.
   *
   * \note Because this iterator has to be copiable,
   * it does not use the multi pass iterator internally,
   * avoiding to copy buffered data every time.
   */
  class MDT_PLAINTEXT_QTCORE_EXPORT BoostSpiritQTextFileInputConstIterator : public boost::iterator_adaptor<
      BoostSpiritQTextFileInputConstIterator,  // Derived
      QTextFileInputConstIterator,        // Base
      uint32_t,                           // Value
      boost::use_default,                 // CategoryOrTraversal
      uint32_t                            // Reference
    >
  {
   public:

    /*! \brief Construct a end-of-file iterator
     */
    BoostSpiritQTextFileInputConstIterator() noexcept
     : iterator_adaptor_( QTextFileInputConstIterator() )
    {
    }

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
    BoostSpiritQTextFileInputConstIterator(QFileDevice *file, const QByteArray & fileEncoding)
     : iterator_adaptor_( QTextFileInputConstIterator(file, fileEncoding) )
    {
      Q_ASSERT( file != nullptr );
      Q_ASSERT( file->isOpen() );
    }

    /*! \brief Copy construct a iterator from \a other
     */
    BoostSpiritQTextFileInputConstIterator(const BoostSpiritQTextFileInputConstIterator & other) noexcept
     : iterator_adaptor_( other.base() )
    {
    }

   private:

    friend class boost::iterator_core_access;

    uint32_t dereference() const
    {
      return base_reference()->unicode();
    }
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_BOOST_SPIRIT_QTEXT_FILE_INPUT_CONST_ITERATOR_H
