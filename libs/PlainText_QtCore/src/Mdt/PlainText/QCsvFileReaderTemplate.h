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
#ifndef MDT_PLAIN_TEXT_QCSV_FILE_READER_TEMPLATE_H
#define MDT_PLAIN_TEXT_QCSV_FILE_READER_TEMPLATE_H

#include "QFileOpenError.h"
#include "Mdt/PlainText/CsvParserSettings.h"
#include "mdt_plaintext_qtcore_export.h"

namespace Mdt{ namespace PlainText{

  /*! \brief CSV file reader template
   *
   * QCsvFileReaderTemplate implements the most part to read CSV files,
   * but let you choose the output containers.
   * In counterpart, it includes all the implementation,
   * which increases the compile time significantly.
   *
   * If you can use QStringList as output records,
   * consider using QCsvFileReader.
   *
   * Here is a minimal example of a possible CSV file reader:
   * \code
   * class MyCsvFileReader
   * {
   *  public:
   *
   *   // All required public methods, constructors, destructors
   *
   *   QStringList readLine() const;
   *
   *  private:
   *
   *   std::unique_ptr<Mdt::PlainText::QCsvFileReaderTemplate> mImpl;
   * };
   * \endcode
   *
   * The implementation of %readLine():
   * \code
   * QStringList MyCsvFileReader::readLine() const
   * {
   *   return mImpl->readLine<QStringList>();
   * }
   * \endcode
   *
   * \note Some part of this API documentation refers to following standards:
   *       \li CSV-1203 available here: https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw
   *       \li RFC 4180 available here: https://tools.ietf.org/html/rfc4180
   * \sa QCsvFileReader
   */
  class MDT_PLAINTEXT_QTCORE_EXPORT QCsvFileReaderTemplate
  {
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_QCSV_FILE_READER_TEMPLATE_H
