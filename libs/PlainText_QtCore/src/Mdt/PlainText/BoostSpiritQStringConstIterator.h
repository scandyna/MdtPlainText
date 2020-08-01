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
#include <boost/iterator/iterator_facade.hpp>
#include <cstdint>

namespace Mdt{ namespace PlainText{

  /*! \brief Iterator adapter to QString::const_iterator
   *
   * Iterator that can be used by parsers based on Boost.Spirit
   *  to be able to parse QString directly.
   *
   * \sa https://stackoverflow.com/questions/57461106/how-can-i-use-boostspirit-x3-in-conjunction-with-qstring
   */
  class MDT_PLAINTEXT_QTCORE_EXPORT BoostSpiritQStringConstIterator : public boost::iterator_facade<
      BoostSpiritQStringConstIterator,    // Derived
      const uint32_t,                     // Value
      boost::random_access_traversal_tag, // CategoryOrTraversal
      const uint32_t &,                   // Reference, see dereference()
      ptrdiff_t                           // Difference
    >
  {
   public:

    /*! \brief Default constructor
     */
    BoostSpiritQStringConstIterator() noexcept
     : mIterator(nullptr)
    {
    }

    /*! \brief Construct a iterator that points to \a it
     *
     * \note Surprisingly, the \a end iterator is required here.
     *  This is because the codepoint value (uint32_t) can be a composition
     *  of 2 UTF16 (QChar) codepoints.
     */
    BoostSpiritQStringConstIterator(QString::const_iterator it, QString::const_iterator end) noexcept
     : mIterator(it)
    {
      setValueAndUpdatePositionIfRequired();
    }

    /*! \brief Constrcut a const iterator from the non const iterator \a it
     *
     * \note Surprisingly, the \a end iterator is required here.
     *  This is because the codepoint value (uint32_t) can be a composition
     *  of 2 UTF16 (QChar) codepoints.
     */
    BoostSpiritQStringConstIterator(QString::iterator it, QString::iterator end) noexcept
     : mIterator(it)
    {
      setValueAndUpdatePositionIfRequired();
    }

    /*! \brief Copy construct a iterator from \a other
     */
    BoostSpiritQStringConstIterator(const BoostSpiritQStringConstIterator & other) noexcept
     : mIterator(other.mIterator)
    {
      setValueAndUpdatePositionIfRequired();
    }

    /*! \brief Get value by index
     */
    uint32_t operator[](ptrdiff_t n) const
    {
      return *(*this + n);
    }

  private:

    friend class boost::iterator_core_access;

    bool equal(const BoostSpiritQStringConstIterator & other) const
    {
      return mIterator == other.mIterator;
    }

    void increment()
    {
      ++mIterator;
      setValueAndUpdatePositionIfRequired();
    }

    void decrement()
    {
      --mIterator;
      setValueAndUpdatePositionIfRequired();
    }

    ptrdiff_t distance_to(const BoostSpiritQStringConstIterator & other) const
    {
      return other.mIterator - mIterator;
    }

    void advance(ptrdiff_t n)
    {
      mIterator += n;
      setValueAndUpdatePositionIfRequired();
    }

    /*! \internal
     *
     * To be recognized as a random access iterator,
     * the reference type MUST be a reference.
     * If not doing so, boost::iterator_facade will
     * tell that this iterator is a input iterator (!)
     *
     * \sa https://github.com/boostorg/iterator/issues/47
     */
    const uint32_t & dereference() const noexcept
    {
      return mValue;
    }

    void setValueAndUpdatePositionIfRequired()
    {
      mValue = mIterator->unicode();
    }

    uint32_t mValue;
    QString::const_iterator mIterator;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_BOOST_SPIRIT_QSTRING_CONST_ITERATOR_H
