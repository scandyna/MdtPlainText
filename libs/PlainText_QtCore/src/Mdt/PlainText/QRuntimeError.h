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
#ifndef MDT_PLAIN_TEXT_QRUNTIME_ERROR_H
#define MDT_PLAIN_TEXT_QRUNTIME_ERROR_H

#include "mdt_plaintext_qtcore_export.h"
#include <QString>
#include <QByteArray>
#include <stdexcept>

namespace Mdt{ namespace PlainText{

  /*! \brief Base class for runtime exceptions using QString messages
   */
  class MDT_PLAINTEXT_QTCORE_EXPORT QRuntimeError : public std::runtime_error
  {
   public:

    /*! \brief Constructor
     */
    explicit QRuntimeError(const QString & what)
     : runtime_error( what.toLocal8Bit().toStdString() )
    {
    }
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_QRUNTIME_ERROR_H
