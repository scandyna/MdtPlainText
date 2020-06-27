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
#ifndef MDT_PLAIN_TEXT_QCSV_FILE_READER_H
#define MDT_PLAIN_TEXT_QCSV_FILE_READER_H

#include "QFileOpenError.h"
#include "QCsvFileReadError.h"
#include "Mdt/PlainText/CsvParserSettings.h"
#include "mdt_plaintext_qtcore_export.h"
#include <QString>
#include <QStringList>
#include <vector>

namespace Mdt{ namespace PlainText{

  class CsvFileReaderTemplate;

  /*! \brief CSV file reader
   *
   * Example of usage:
   * \code
   * Mdt::PlainText::QCsvFileReader csvReader;
   *
   * csvReader.setFilePath("/some/path/to/file.csv");
   * csvReader.setFileEncoding("ISO 8859-1");
   * csvReader.open();
   * while( !csvReader.atEnd() ){
   *   processRecord( csvReader.readLine() );
   * }
   * csvReader.close();
   * \endcode
   *
   * If you need a other output than QStringList,
   * take a look at QCsvFileReaderTemplate.
   *
   * \note Some part of this API documentation refers to following standards:
   *       \li CSV-1203 available here: https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw
   *       \li RFC 4180 available here: https://tools.ietf.org/html/rfc4180
   * \sa QCsvFileReaderTemplate
   */
  class MDT_PLAINTEXT_QTCORE_EXPORT QCsvFileReader
  {
   public:

    /*! \brief Construct a CSV file reader
     */
    QCsvFileReader();

    /*! \brief Cleanup this CSV file reader
     */
    ~QCsvFileReader();

    QCsvFileReader(const QCsvFileReader &) = delete;
    QCsvFileReader & operator=(const QCsvFileReader &) = delete;
    QCsvFileReader(QCsvFileReader &&) = delete;
    QCsvFileReader & operator=(QCsvFileReader &&) = delete;

    /*! \brief Set the path to the file
     *
     * \pre \a filePath must not be empty
     * \pre This file reader must not be open
     * \sa isOpen()
     */
    void setFilePath(const QString & filePath);

    /*! \brief Get the path to the file
     *
     * \sa setFilePath()
     */
    const QString & filePath() const noexcept;

    /*! \brief Set CSV settings
     *
     * \pre \a settings must be valid
     * \pre This file reader must not be open
     * \sa isOpen()
     */
    void setCsvSettings(const CsvParserSettings & settings) noexcept;

    /*! \brief Get CSV settings
     */
    const CsvParserSettings & csvSettings() const noexcept;

    /*! \brief Open this CSV file reader
     *
     * If this file reader is allready open,
     * it will be closed first().
     *
     * Open the file set with setFilePath().
     *
     * \exception QFileOpenError
     * \pre A path to a file must have been set
     * \sa setFilePath()
     * \sa close()
     */
    void open();

    /*! \brief Check if this file reader is open
     *
     * \sa open()
     */
    bool isOpen() const;

    /*! \brief Check if this file reader is at end
     *
     * \pre This file reader must be open
     * \sa isOpen()
     */
    bool atEnd() const noexcept;

    /*! \brief Read a line from the CSV file
     *
     * \exception QCsvFileReadError
     * \pre This file reader must be open
     * \pre This file reader must not be at end
     * \sa isOpen()
     * \sa atEnd()
     */
    QStringList readLine() const;

    /*! \brief Read all lines from the CSV file
     *
     * \exception QCsvFileReadError
     * \pre This file reader must be open
     * \pre This file reader must not be at end (i.e. the file must not be empty)
     * \sa isOpen()
     * \sa atEnd()
     */
    std::vector<QStringList> readAll() const;

    /*! \brief Close this file reader
     */
    void close();

  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_QCSV_FILE_READER_H
