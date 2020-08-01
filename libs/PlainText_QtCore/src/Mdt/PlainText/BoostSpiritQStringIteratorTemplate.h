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
#ifndef MDT_PLAIN_TEXT_BOOST_SPIRIT_QSTRING_ITERATOR_TEMPLATE_H
#define MDT_PLAIN_TEXT_BOOST_SPIRIT_QSTRING_ITERATOR_TEMPLATE_H

#include <boost/iterator/iterator_facade.hpp>
#include <type_traits>

namespace Mdt{ namespace PlainText{

  /*! \brief Iterator adapter template to QString::[const_]iterator
   *
   * Iterator that can be used by parsers based on Boost.Spirit
   *  to be able to parse QString directly.
   *
   * \sa BoostSpiritQStringIterator
   * \sa BoostSpiritQStringConstIterator
   * \sa https://stackoverflow.com/questions/57461106/how-can-i-use-boostspirit-x3-in-conjunction-with-qstring
   */
  template<typename BaseIterator, typename Value>
  class BoostSpiritQStringIteratorTemplate : public boost::iterator_facade<
      BoostSpiritQStringIteratorTemplate<BaseIterator, Value>,  // Derived
      Value,                                                    // Value
      boost::random_access_traversal_tag,                       // CategoryOrTraversal
      Value &,                                                  // Reference, see dereference()
      ptrdiff_t                                                 // Difference
    >
  {
   public:

    /*! \brief Default constructor
     */
    BoostSpiritQStringIteratorTemplate() noexcept
     : mIterator(nullptr)
    {
    }

    /*! \brief Construct a iterator that points to \a it
     */
    BoostSpiritQStringIteratorTemplate(BaseIterator it) noexcept
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
//     const uint32_t & dereference() const
//     {
//       mValue = mIterator->unicode();
//       return mValue;
//     }

    Value & dereference()
    {
    }

    mutable Value mValue;
    BaseIterator mIterator;
    struct enabler {};
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_BOOST_SPIRIT_QSTRING_ITERATOR_TEMPLATE_H
