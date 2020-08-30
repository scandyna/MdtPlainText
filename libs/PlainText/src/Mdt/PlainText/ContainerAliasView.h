/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_CONTAINER_ALIAS_VIEW_H
#define MDT_PLAIN_TEXT_CONTAINER_ALIAS_VIEW_H

#include "ContainerAliasViewConstIterator.h"
#include <iterator>
#include <cassert>

namespace Mdt{ namespace PlainText{

  /*! \brief A view on a container that exposes its value as alias
   *
   * A example of a use case is Mdt::PlainText::QStringListUnicodeView
   * that exposes a QStringList as a list of Mdt::PlainText::QStringUnicodeView .
   *
   * Example:
   * \code
   * using namespace Mdt::PlainText;
   *
   * using StringTable = std::vector<QStringList>;
   * using StringTableUnicodeView = ContainerAliasView<StringTable, QStringListUnicodeView>;
   *
   * StringTable table{...};
   * StringTableUnicodeView view(table);
   *
   * for(const QStringListUnicodeView & record : table){
   *   processRecord(record);
   * }
   * \endcode
   */
  template<typename SourceContainer, typename AliasValue>
  class ContainerAliasView
  {
   public:

    /*! \brief STL container value_type
     */
    using value_type = AliasValue;

    /*! \brief STL container size_type
     */
    using size_type = int;

    /*! \brief STL container const_iterator
     */
    using const_iterator = ContainerAliasViewConstIterator<typename SourceContainer::const_iterator, AliasValue>;

    ContainerAliasView() = delete;

    /*! \brief Construct a view from \a container
     */
    explicit ContainerAliasView(const SourceContainer & container)
     : mBegin( container.cbegin() ),
       mEnd( container.cend() )
    {
    }

    /*! \brief Copy construct a view from \a other
     */
    ContainerAliasView(const ContainerAliasView & other) = default;

    /*! \brief Copy assign \a other to this view
     */
    ContainerAliasView & operator=(const ContainerAliasView & other) = default;

    /*! \brief Move construct a view from \a other
     */
    ContainerAliasView(ContainerAliasView && other) noexcept = default;

    /*! \brief Move assign \a other to this view
     */
    ContainerAliasView & operator=(ContainerAliasView && other) noexcept = default;

    /*! \brief Return the number of elements in the container
     */
    int size() const noexcept
    {
      return std::distance(mBegin, mEnd);
    }

    /*! \brief Get a alias value for the element at \a index
     *
     * \pre \a index must be in valid range ( 0 >= \a index < size() )
     */
    AliasValue at(int index) const
    {
      assert( index >= 0 );
      assert( index < size() );

      return *std::next(mBegin, index);
    }

    /*! \brief Get a iterator to the beginning
     */
    const_iterator begin() const noexcept
    {
      return mBegin;
    }

    /*! \brief Get a iterator to the end
     */
    const_iterator end() const noexcept
    {
      return mEnd;
    }

    /*! \brief Get a iterator to the beginning
     */
    const_iterator cbegin() const noexcept
    {
      return mBegin;
    }

    /*! \brief Get a iterator to the end
     */
    const_iterator cend() const noexcept
    {
      return mEnd;
    }

   private:

    const_iterator mBegin;
    const_iterator mEnd;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_CONTAINER_ALIAS_VIEW_H
