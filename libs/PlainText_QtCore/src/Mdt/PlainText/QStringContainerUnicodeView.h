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
#ifndef MDT_PLAIN_TEXT_QSTRING_CONTAINER_UNICODE_VIEW_H
#define MDT_PLAIN_TEXT_QSTRING_CONTAINER_UNICODE_VIEW_H

#include "QStringUnicodeView.h"
#include "QStringContainerUnicodeConstIterator.h"
#include <iterator>
#include <cassert>

namespace Mdt{ namespace PlainText{

  /*! \brief QStringContainerUnicodeView is a view on a container of QString to access its elements as QStringUnicodeView
   *
   * Example:
   * \code
   * using Mdt::PlainText::QStringUnicodeView;
   * using StringRecord = std::vector<QString>;
   * using StringRecordUnicodeView = Mdt::PlainText::QStringContainerUnicodeView<StringRecord>;
   *
   * StringRecord record{"ABC","1234"};
   * StringRecordUnicodeView recordUnicodeView(record);
   *
   * for(const QStringUnicodeView & unicodeString : recordUnicodeView){
   *   processUnicodeString(unicodeString);
   * }
   * \endcode
   *
   * \sa QStringListUnicodeView
   */
  template<typename Container>
  class QStringContainerUnicodeView
  {
   public:

    /*! \brief STL container value_type
     */
    using value_type = QStringUnicodeView;

    /*! \brief STL container size_type
     */
    using size_type = int;

    /*! \brief STL container const_iterator
     */
    using const_iterator = QStringContainerUnicodeConstIterator<typename Container::const_iterator>;

    QStringContainerUnicodeView() = delete;

    /*! \brief Construct a view from \a container
     */
    explicit QStringContainerUnicodeView(const Container & container) noexcept
     : mBegin( container.cbegin() ),
       mEnd( container.cend() )
    {
    }

    /*! \brief Copy construct a view from \a other
     */
    QStringContainerUnicodeView(const QStringContainerUnicodeView & other) noexcept = default;

    /*! \brief Copy assign \a other to this view
     */
    QStringContainerUnicodeView & operator=(const QStringContainerUnicodeView & other) noexcept = default;

    /*! \brief Move construct a view from \a other
     */
    QStringContainerUnicodeView(QStringContainerUnicodeView && other) noexcept = default;

    /*! \brief Move assign \a other to this view
     */
    QStringContainerUnicodeView & operator=(QStringContainerUnicodeView && other) noexcept = default;

    /*! \brief Return the number of element in this container
     */
    int size() const noexcept
    {
      return std::distance(mBegin, mEnd);
    }

    /*! \brief Get a unicode string view for the element at \a index
     *
     * \pre \a index must be in valid range ( 0 >= \a index < size() )
     */
    QStringUnicodeView at(int index) const
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

#endif // #ifndef MDT_PLAIN_TEXT_QSTRING_CONTAINER_UNICODE_VIEW_H
