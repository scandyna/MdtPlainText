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
#ifndef MDT_PLAIN_TEXT_QSTRING_LIST_UNICODE_VIEW_H
#define MDT_PLAIN_TEXT_QSTRING_LIST_UNICODE_VIEW_H

#include "QStringUnicodeView.h"
#include <QStringList>
#include <QList>
#include <cassert>

namespace Mdt{ namespace PlainText{

  /*! \brief QStringListUnicodeView is a view on a QStringList to access its elements as QStringUnicodeView
   *
   * Example:
   * \code
   * QStringList stringList{"ABC","1234"};
   * Mdt::PlainText::QStringListUnicodeView unicodeStringList(stringList);
   *
   * for(const QStringUnicodeView & unicodeString : unicodeStringList){
   *   processUnicodeString(unicodeString);
   * }
   * \endcode
   */
  class QStringListUnicodeView
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
    using const_iterator = void;

    QStringListUnicodeView() = delete;

    /*! \brief Construct a karma record from \a record
     */
    constexpr
    explicit QStringListUnicodeView(const QStringList & record) noexcept
    {
    }

    /*! \brief Copy construct a container from \a other
     */
    constexpr
    QStringListUnicodeView(const QStringListUnicodeView & other) noexcept = default;

    /*! \brief Copy assign \a other to this container
     */
    constexpr
    QStringListUnicodeView & operator=(const QStringListUnicodeView & other) noexcept = default;

    /*! \brief Move construct a container from \a other
     */
    constexpr
    QStringListUnicodeView(QStringListUnicodeView && other) noexcept = default;

    /*! \brief Move assign \a other to this container
     */
    constexpr
    QStringListUnicodeView & operator=(QStringListUnicodeView && other) noexcept = default;

    /*! \brief Return the number of element in this list
     */
    int size() const noexcept
    {
    }

    /*! \brief Get the element at \a index
     *
     * \pre \a index must be in valid range ( 0 >= \a index < size() )
     */
    QStringUnicodeView at(int index) const
    {
      assert( index >= 0 );
      assert( index < size() );
    }
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_QSTRING_LIST_UNICODE_VIEW_H
