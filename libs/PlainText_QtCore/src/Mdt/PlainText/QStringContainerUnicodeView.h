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
#include "Mdt/PlainText/ContainerAliasView.h"
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
  using QStringContainerUnicodeView = ContainerAliasView<Container, QStringUnicodeView>;

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_QSTRING_CONTAINER_UNICODE_VIEW_H
