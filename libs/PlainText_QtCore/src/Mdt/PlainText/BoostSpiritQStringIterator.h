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
#ifndef MDT_PLAIN_TEXT_BOOST_SPIRIT_QSTRING_ITERATOR_H
#define MDT_PLAIN_TEXT_BOOST_SPIRIT_QSTRING_ITERATOR_H

#include "BoostSpiritQStringIteratorTemplate.h"
#include <QString>
#include <cstdint>

#include "mdt_plaintext_qtcore_export.h"
#include <QString>
#include <boost/iterator/iterator_facade.hpp>
#include <cstdint>


namespace Mdt{ namespace PlainText{

  /*! \brief Iterator adapter to QString::iterator
   *
   * Iterator that can be used by parsers based on Boost.Spirit
   *  to be able to parse QString directly.
   */
//   using BoostSpiritQStringIterator = BoostSpiritQStringIteratorTemplate<QString::iterator, uint32_t>;

  class MDT_PLAINTEXT_QTCORE_EXPORT BoostSpiritQStringIterator : public boost::iterator_facade<
      BoostSpiritQStringIterator,         // Derived
      uint32_t,                           // Value
      boost::random_access_traversal_tag, // CategoryOrTraversal
      uint32_t &,                         // Reference, see dereference()
      ptrdiff_t                           // Difference
    >
  {
   public:

    /*! \brief Default constructor
     */
    BoostSpiritQStringIterator() noexcept
     : mIterator(nullptr)
    {
    }

    /*! \brief Construct a iterator that points to \a it
     */
    BoostSpiritQStringIterator(QString::iterator it) noexcept
     : mIterator(it)
    {
    }

  private:

    friend class boost::iterator_core_access;

    /*! \internal
     *
     * To be recognized as a random access iterator,
     * the reference type MUST be a reference.
     * If not doing so, boost::iterator_facade will
     * tell that this iterator is a input iterator (!)
     *
     * \sa https://github.com/boostorg/iterator/issues/47
     */
    uint32_t & dereference() const
    {
      /// \todo Maybe a lambda ?? Maybe mValue which is a lazy function ??
//       return static_cast<uint32_t &>( mIterator->unicode() );
//       return const_cast<BoostSpiritQStringIterator*>(this)->mIterator->unicode();
    }

    QString::iterator mIterator;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_BOOST_SPIRIT_QSTRING_ITERATOR_H
