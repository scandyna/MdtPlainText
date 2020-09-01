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

#include "QStringContainerUnicodeView.h"
#include "QStringUnicodeView.h"
#include <QStringList>
#include <QList>

namespace Mdt{ namespace PlainText{

  /*! \brief QStringListUnicodeView is a view on a QStringList to access its elements as QStringUnicodeView
   *
   * Example:
   * \code
   * using Mdt::PlainText::QStringUnicodeView;
   *
   * QStringList stringList{"ABC","1234"};
   * Mdt::PlainText::QStringListUnicodeView unicodeStringList(stringList);
   *
   * for(const QStringUnicodeView & unicodeString : unicodeStringList){
   *   processUnicodeString(unicodeString);
   * }
   * \endcode
   */
  using QStringListUnicodeView = QStringContainerUnicodeView<QStringList>;

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_QSTRING_LIST_UNICODE_VIEW_H
