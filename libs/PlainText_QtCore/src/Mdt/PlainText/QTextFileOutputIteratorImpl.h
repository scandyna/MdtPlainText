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
#ifndef MDT_PLAIN_TEXT_QTEXT_FILE_OUTPUT_ITERATOR_IMPL_H
#define MDT_PLAIN_TEXT_QTEXT_FILE_OUTPUT_ITERATOR_IMPL_H

#include "QFileWriteError.h"
#include "QTextCodecNotFoundError.h"
#include "mdt_plaintext_qtcore_export.h"
#include <QObject>
#include <QFileDevice>
#include <QByteArray>
#include <QFileDevice>
#include <QTextEncoder>
#include <QPointer>
#include <memory>
#include <cassert>

namespace Mdt{ namespace PlainText{

  /*! \internal Implementation part for QTextFileOutputIterator
   */
  class MDT_PLAINTEXT_QTCORE_EXPORT QTextFileOutputIteratorImpl : public QObject
  {
    Q_OBJECT

   public:

    /*! \brief Constructor
     *
     * \pre \a file must be a valid pointer
     * \pre \a file must be open with a writable mode
     * \exception QTextCodecNotFoundError
     */
    explicit QTextFileOutputIteratorImpl(QFileDevice *file, const QByteArray & fileEncoding);

    QTextFileOutputIteratorImpl(const QTextFileOutputIteratorImpl &) = delete;
    QTextFileOutputIteratorImpl & operator=(const QTextFileOutputIteratorImpl &) = delete;

    QTextFileOutputIteratorImpl(const QTextFileOutputIteratorImpl &&) = delete;
    QTextFileOutputIteratorImpl & operator=(QTextFileOutputIteratorImpl &&) = delete;

    /*! \brief Write a code unite to the file
     *
     * \exception QFileWriteError
     */
    void put(const QChar & c);

    static
    bool fileOpenModeIsWritable(const QFileDevice & file)
    {
      const auto flags = file.openMode();

      if( flags.testFlag(QIODevice::WriteOnly) ){
        return true;
      }

      return false;
    }

   private:

    std::unique_ptr<QTextEncoder> mEncoder;
    QPointer<QFileDevice> mFile;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_QTEXT_FILE_OUTPUT_ITERATOR_IMPL_H
