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
#ifndef MDT_PLAIN_TEXT_TEST_LIB_TEXT_FILE_UTILS_H
#define MDT_PLAIN_TEXT_TEST_LIB_TEXT_FILE_UTILS_H

#include "mdt_plaintext_testlib_export.h"
#include <QFile>
#include <QString>

namespace Mdt{ namespace PlainText{ namespace TestLib{

  /*! \internal Write a text file
   */
  MDT_PLAINTEXT_TESTLIB_EXPORT
  bool writeTextFileUtf8(QFile & file, const QString & content);

}}} // namespace Mdt{ namespace PlainText{ namespace TestLib{

#endif // #ifndef MDT_PLAIN_TEXT_TEST_LIB_TEXT_FILE_UTILS_H
