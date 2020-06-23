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
#ifndef MDT_PLAIN_TEXT_BOOST_SPIRIT_QSTRING_CONST_ITERATOR_H
#define MDT_PLAIN_TEXT_BOOST_SPIRIT_QSTRING_CONST_ITERATOR_H

#include "mdt_plaintext_qtcore_export.h"
#include <QString>
#include <boost/iterator/iterator_adaptor.hpp>
#include <cstdint>

namespace Mdt{ namespace PlainText{

  /*! \brief Iterator adapter to QString::const_iterator
   *
   * Iterator that can be used by parsers based on Boost.Spirit
   *  to be able to parse QString directly.
   *
   * \sa https://stackoverflow.com/questions/57461106/how-can-i-use-boostspirit-x3-in-conjunction-with-qstring
   */
  class MDT_PLAINTEXT_QTCORE_EXPORT BoostSpiritQStringConstIterator : public boost::iterator_adaptor<
      BoostSpiritQStringConstIterator,  // Derived
      QString::const_iterator,          // Base
      uint32_t,                         // Value
      boost::use_default,               // CategoryOrTraversal
      uint32_t>                         // Reference
  {
   public:

    /*! \brief Default constructor
     */
    BoostSpiritQStringConstIterator() noexcept
     : iterator_adaptor_(nullptr)
    {
    }

    /*! \brief Construct a iterator that points to \a it
     */
    BoostSpiritQStringConstIterator(QString::const_iterator it) noexcept
     : iterator_adaptor_(it)
    {
    }

    /*! \brief Constrcut a const iterator from the non const iterator \a it
     */
    BoostSpiritQStringConstIterator(QString::iterator it) noexcept
     : iterator_adaptor_(it)
    {
    }

    /*! \brief Copy construct a iterator from \a other
     */
    BoostSpiritQStringConstIterator(const BoostSpiritQStringConstIterator & other) noexcept
     : iterator_adaptor_( other.base() )
    {
    }

    /*! \brief Get value by index
     */
    uint32_t operator[](difference_type n) const
    {
      return *(*this + n);
    }

  private:

    friend class boost::iterator_core_access;

    uint32_t dereference() const
    {
      return static_cast<uint32_t>( this->base_reference()->unicode() );
    }
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_BOOST_SPIRIT_QSTRING_CONST_ITERATOR_H
