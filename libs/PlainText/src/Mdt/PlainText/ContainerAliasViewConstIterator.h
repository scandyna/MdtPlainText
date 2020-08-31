/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_CONTAINER_ALIAS_VIEW_CONST_ITERATOR_H
#define MDT_PLAIN_TEXT_CONTAINER_ALIAS_VIEW_CONST_ITERATOR_H

#include <type_traits>
#include <iterator>

namespace Mdt{ namespace PlainText{

  /*! \brief A iterator adaptor for a source container that returns its elements as alias values
   *
   * \sa ContainerAliasView
   */
  template<typename SourceIterator, typename AliasValue>
  class ContainerAliasViewConstIterator
  {
   public:

    /*! \brief STL iterator difference_type
     */
    using difference_type = typename SourceIterator::difference_type;

    /*! \brief STL iterator value_type
     */
    using value_type = const AliasValue;

    /*! \brief STL iterator pointer
     */
    using pointer = value_type;

    /*! \brief STL iterator reference
     */
    using reference = value_type;

    /*! \brief STL iterator iterator_category
     */
    using iterator_category = std::bidirectional_iterator_tag;

    /*! \brief Default constructor
     */
    ContainerAliasViewConstIterator() = default;

    /*! \brief Construct a iterator that points to \a it
     */
    explicit ContainerAliasViewConstIterator(SourceIterator it)
     : mSourceIterator(it)
    {
    }

    /*! \brief Copy construct a iterator from \a other
     */
    ContainerAliasViewConstIterator(const ContainerAliasViewConstIterator & other) = default;

    /*! \brief Copy assign \a other to this iterator
     */
    ContainerAliasViewConstIterator & operator=(const ContainerAliasViewConstIterator & other) = default;

    /*! \brief Move construct a iterator from \a other
     */
    ContainerAliasViewConstIterator(ContainerAliasViewConstIterator && other) noexcept = default;

    /*! \brief Move assign \a other to this iterator
     */
    ContainerAliasViewConstIterator & operator=(ContainerAliasViewConstIterator && other) noexcept = default;

    /*! \brief Get the alias value
     */
    value_type operator*() const
    {
      return AliasValue(*mSourceIterator);
    }

    /*! \brief Increment iterator (pre-increment)
     */
    ContainerAliasViewConstIterator & operator++()
    {
      ++mSourceIterator;
      return *this;
    }

    /*! \brief Increment iterator (post-increment)
     */
    ContainerAliasViewConstIterator operator++(int)
    {
      ContainerAliasViewConstIterator tmp(*this);
      ++*this;
      return tmp;
    }

    /*! \brief Decrement iterator (pre-decrement)
     */
    ContainerAliasViewConstIterator & operator--()
    {
      --mSourceIterator;
      return *this;
    }

    /*! \brief Decrement iterator (post-decrement)
     */
    ContainerAliasViewConstIterator operator--(int)
    {
      ContainerAliasViewConstIterator tmp(*this);
      --*this;
      return tmp;
    }

    /*! \brief Returns true if iterator a refers to same item than iterator b
     */
    friend
    bool operator==(const ContainerAliasViewConstIterator & a, const ContainerAliasViewConstIterator & b) noexcept
    {
      return a.mSourceIterator == b.mSourceIterator;
    }

    /*! \brief Returns true if iterator a refers not to same item than iterator b
     */
    friend
    bool operator!=(const ContainerAliasViewConstIterator & a, const ContainerAliasViewConstIterator & b) noexcept
    {
      return !(a == b);
    }

   private:

    SourceIterator mSourceIterator = SourceIterator{};
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_CONTAINER_ALIAS_VIEW_CONST_ITERATOR_H
