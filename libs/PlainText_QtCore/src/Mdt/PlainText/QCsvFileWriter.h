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
#ifndef MDT_PLAIN_TEXT_QCSV_FILE_WRITER_H
#define MDT_PLAIN_TEXT_QCSV_FILE_WRITER_H

#include "QFileOpenError.h"
#include "Mdt/PlainText/CsvGeneratorSettings.h"
#include "Mdt/PlainText/FileWriteOpenMode.h"
#include "mdt_plaintext_qtcore_export.h"
#include <QString>
#include <QByteArray>
#include <memory>

namespace Mdt{ namespace PlainText{

  class QCsvFileWriterTemplate;

  /*! \brief CSV file writer
   *
   * Example of usage:
   * \code
   * Mdt::PlainText::QCsvFileWriter csvWriter;
   *
   * csvWriter.setFilePath("/some/path/to/file.csv");
   * csvWriter.setFileEncoding("ISO 8859-1");
   * csvWriter.open();
   * csvWriter.appendRecord({"A","B","C"});
   * \endcode
   */
  class MDT_PLAINTEXT_QTCORE_EXPORT QCsvFileWriter
  {
   public:

    /*! \brief Construct a CSV file writer
     */
    QCsvFileWriter();

    /*! \brief Cleanup this CSV file writer
     */
    ~QCsvFileWriter();

    QCsvFileWriter(const QCsvFileWriter &) = delete;
    QCsvFileWriter & operator=(const QCsvFileWriter &) = delete;
    QCsvFileWriter(QCsvFileWriter &&) = delete;
    QCsvFileWriter & operator=(QCsvFileWriter &&) = delete;

    /*! \brief Set the path to the file
     *
     * \pre \a filePath must not be empty
     * \pre This file writer must not be open
     * \sa isOpen()
     */
    void setFilePath(const QString & filePath);

    /*! \brief Get the path to the file
     *
     * \sa setFilePath()
     */
    QString filePath() const;

    /*! \brief Set the file encoding
     *
     * The default encoding is UTF-8
     *
     * \pre \a encoding must not be empty
     * \pre This file reader must not be open
     * \sa isOpen()
     */
    void setFileEncoding(const QByteArray & encoding);

    /*! \brief Get the file encoding
     *
     * \sa setFileEncoding()
     */
    const QByteArray & fileEncoding() const noexcept;

    /*! \brief Set CSV settings
     *
     * \pre \a settings must be valid
     * \pre This file writer must not be open
     * \sa isOpen()
     */
    void setCsvSettings(const CsvGeneratorSettings & settings) noexcept;

    /*! \brief Get CSV settings
     */
    const CsvGeneratorSettings & csvSettings() const noexcept;

    /*! \brief Set the open mode for this writer
     *
     * The default open mode is FileWriteOpenMode::Append
     *
     * \pre This file writer must not be open
     * \sa isOpen()
     */
    void setOpenMode(FileWriteOpenMode mode);

    /*! \brief Get the open mode
     */
    FileWriteOpenMode openMode() const noexcept;

    /*! \brief Open this CSV file writer
     *
     * If this file writer is allready open,
     * it will be closed first().
     *
     * Open the file set with setFilePath().
     *
     * \exception FileOpenError
     * \pre A path to a file must have been set
     * \sa setFilePath()
     * \sa close()
     */
    void open();

    /*! \brief Check if this file writer is open
     *
     * \sa open()
     */
    bool isOpen() const;

    /*! \brief Append a record to this CSV file
     *
     * \code
     * csvWriter.appendRecord({"A","B","C"});
     * \endcode
     *
     * \code
     * csvWriter.appendRecord({
     *   {"A",CsvGeneratorField::Quote},
     *   {"2",CsvGeneratorField::DoNotQuote},
     *   "C"
     * });
     * \endcode
     */

    /*! \brief Close this file writer
     */
    void close();

   private:

    std::unique_ptr<QCsvFileWriterTemplate> mImpl;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_QCSV_FILE_WRITER_H
