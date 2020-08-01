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
#ifndef MDT_PLAIN_TEXT_QCSV_FILE_WRITER_TEMPLATE_H
#define MDT_PLAIN_TEXT_QCSV_FILE_WRITER_TEMPLATE_H

#include "QFileOpenError.h"
#include "Mdt/PlainText/CsvGeneratorSettings.h"
#include "Mdt/PlainText/FileWriteOpenMode.h"
#include "mdt_plaintext_qtcore_export.h"
#include <QString>
#include <QByteArray>
#include <QFile>
#include <cassert>

namespace Mdt{ namespace PlainText{

  /*! \brief CSV file writer template
   *
   * QCsvFileWriterTemplate implements the most part to write CSV files,
   * but let you choose the input containers.
   * In counterpart, it includes all the implementation,
   * which increases the compile time significantly.
   *
   * If you can use std::vector<QCsvGeneratorField> or QStringList as input records,
   * consider using QCsvFileWriter.
   *
   * Here is a minimal example of a possible CSV file writer:
   * \code
   * class MyCsvFileWriter
   * {
   *  public:
   *
   *   // All required public methods, constructors, destructor
   *
   *   void appendLine(cont MyRecord & record);
   *
   *  private:
   *
   *   std::unique_ptr<Mdt::PlainText::QCsvFileWriterTemplate> mImpl;
   * };
   * \endcode
   *
   * \todo Check if this is correct
   * The implementation of %appendLine():
   * \code
   * void MyCsvFileWriter::appendLine(const MyRecord & record)
   * {
   *   using DestinationIterator = QCsvFileWriterTemplate::iterator;
   *
   *   // A boost Spirit Karma rule
   *   MyRecordRule<DestinationIterator, MyRecord> rule( csvSettings() );
   *
   *   mImpl->appendLine(record, rule);
   * }
   * \endcode
   *
   * \sa CsvFileWriter
   */
  class MDT_PLAINTEXT_QTCORE_EXPORT QCsvFileWriterTemplate
  {
   public:

    /*! \brief Construct a CSV file writer
     */
    QCsvFileWriterTemplate() = default;

    /*! \brief Cleanup this CSV file writer
     */
    ~QCsvFileWriterTemplate()
    {
      close();
    }

    QCsvFileWriterTemplate(const QCsvFileWriterTemplate &) = delete;
    QCsvFileWriterTemplate & operator=(const QCsvFileWriterTemplate &) = delete;
    QCsvFileWriterTemplate(QCsvFileWriterTemplate &&) = delete;
    QCsvFileWriterTemplate & operator=(QCsvFileWriterTemplate &&) = delete;

    /*! \brief Set the path to the file
     *
     * \pre \a filePath must not be empty
     * \pre This file writer must not be open
     * \sa isOpen()
     */
    void setFilePath(const QString & filePath)
    {
      assert( !filePath.isEmpty() );
      assert( !isOpen() );

      mFile.setFileName(filePath);
    }

    /*! \brief Get the path to the file
     *
     * \sa setFilePath()
     */
    QString filePath() const
    {
      return mFile.fileName();
    }

    /*! \brief Set the file encoding
     *
     * The default encoding is UTF-8
     *
     * \pre \a encoding must not be empty
     * \pre This file reader must not be open
     * \sa isOpen()
     */
    void setFileEncoding(const QByteArray & encoding)
    {
      Q_ASSERT( !encoding.isEmpty() );
      assert( !isOpen() );

      mFileEncoding = encoding;
    }

    /*! \brief Get the file encoding
     *
     * \sa setFileEncoding()
     */
    const QByteArray & fileEncoding() const noexcept
    {
      return mFileEncoding;
    }

    /*! \brief Set CSV settings
     *
     * \pre \a settings must be valid
     * \pre This file writer must not be open
     * \sa isOpen()
     */
    void setCsvSettings(const CsvGeneratorSettings & settings) noexcept
    {
      assert( settings.isValid() );
      assert( !isOpen() );

      mCsvSettings = settings;
    }

    /*! \brief Get CSV settings
     */
    const CsvGeneratorSettings & csvSettings() const noexcept
    {
      return mCsvSettings;
    }

    /*! \brief Set the open mode for this writer
     *
     * The default open mode is FileWriteOpenMode::Append
     *
     * \pre This file writer must not be open
     * \sa isOpen()
     */
    void setOpenMode(FileWriteOpenMode mode)
    {
      assert( !isOpen() );

      mOpenMode = mode;
    }

    /*! \brief Get the open mode
     */
    FileWriteOpenMode openMode() const noexcept
    {
      return mOpenMode;
    }

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
    void open()
    {
      assert( !filePath().isEmpty() );
    }

    /*! \brief Check if this file writer is open
     *
     * \sa open()
     */
    bool isOpen() const
    {
      return mFile.isOpen();
    }

    /*! \brief Append a record to this CSV file
     */

    /*! \brief Close this file writer
     */
    void close()
    {
      mFile.close();
    }

   private:

    QFile mFile;
    QByteArray mFileEncoding = "UTF-8";
    CsvGeneratorSettings mCsvSettings;
    FileWriteOpenMode mOpenMode;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_QCSV_FILE_WRITER_TEMPLATE_H
