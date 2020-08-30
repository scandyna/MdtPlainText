/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_CONTAINER_ALIAS_VIEW_CONST_ITERATOR_H
#define MDT_PLAIN_TEXT_CONTAINER_ALIAS_VIEW_CONST_ITERATOR_H

#include <boost/iterator/iterator_facade.hpp>

namespace Mdt{ namespace PlainText{

  /*! \brief A iterator adaptor for a source container that returns its elements as alias values
   *
   * \sa ContainerAliasView
   */
  template<typename SourceIterator, typename AliasValue>
  class ContainerAliasViewConstIterator : public boost::iterator_facade<
      ContainerAliasViewConstIterator<SourceIterator, AliasValue>,  // Derived
      const AliasValue,                                             // Value
      boost::bidirectional_traversal_tag,                           // CategoryOrTraversal
      const AliasValue &,                                           // Reference, see dereference()
      typename SourceIterator::difference_type                      // Difference
    >
  {
   public:

    /*! \brief Default constructor
     */
    ContainerAliasViewConstIterator() = default;

    /*! \brief Construct a iterator that points to \a it
     */
    explicit ContainerAliasViewConstIterator(SourceIterator it)
     : mSourceIterator(it)
    {
    }

   private:

    friend class boost::iterator_core_access;

    bool equal(const ContainerAliasViewConstIterator & other) const noexcept
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
    const AliasValue & dereference() const noexcept
    {
      mValue = AliasValue(*mSourceIterator);
      return mValue;
    }

    SourceIterator mSourceIterator = SourceIterator{};
    mutable AliasValue mValue;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_CONTAINER_ALIAS_VIEW_CONST_ITERATOR_H
