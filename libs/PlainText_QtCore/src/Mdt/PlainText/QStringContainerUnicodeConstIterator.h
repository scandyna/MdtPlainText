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
#ifndef MDT_PLAIN_TEXT_QSTRING_CONTAINER_UNICODE_CONST_ITERATOR_H
#define MDT_PLAIN_TEXT_QSTRING_CONTAINER_UNICODE_CONST_ITERATOR_H

#include "QStringUnicodeView.h"
#include <boost/iterator/iterator_facade.hpp>

namespace Mdt{ namespace PlainText{

  /*! \brief A iterator adaptor for a container of QString that returns its elements as QStringUnicodeView
   *
   * \sa QStringListUnicodeView
   */
  template<typename SourceIterator>
  class QStringContainerUnicodeConstIterator  : public boost::iterator_facade<
      QStringContainerUnicodeConstIterator<SourceIterator>, // Derived
      const QStringUnicodeView,                             // Value
      boost::bidirectional_traversal_tag,                   // CategoryOrTraversal
      const QStringUnicodeView &,                           // Reference, see dereference()
      ptrdiff_t                                             // Difference
    >
  {
   public:

    /*! \brief Default constructor
     */
    QStringContainerUnicodeConstIterator() noexcept = default;

    /*! \brief Construct a iterator that points to \a it
     */
    explicit QStringContainerUnicodeConstIterator(SourceIterator it) noexcept
     : mSourceIterator(it)
    {
    }

   private:

    friend class boost::iterator_core_access;

    bool equal(const QStringContainerUnicodeConstIterator & other) const noexcept
    {
      return mSourceIterator == other.mSourceIterator;
    }

    void increment() noexcept
    {
      ++mSourceIterator;
    }

    void decrement() noexcept
    {
      --mSourceIterator;
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
    const QStringUnicodeView & dereference() const noexcept
    {
      mValue = *mSourceIterator;
      return mValue;
    }

    SourceIterator mSourceIterator = SourceIterator{};
    mutable QStringUnicodeView mValue;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_QSTRING_CONTAINER_UNICODE_CONST_ITERATOR_H
