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
#include "Mdt/PlainText/CsvParserTemplate.h"
#include "mdt_plaintext_qtcore_export.h"
#include <QString>
#include <QObject>

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
  class MDT_PLAINTEXT_QTCORE_EXPORT QCsvFileReaderTemplate : public QObject
  {
    Q_OBJECT

   public:

    /*! \brief Construct a CSV file reader
     */
    explicit QCsvFileReaderTemplate(QObject *parent = nullptr)
     : QObject(parent)
    {
    }

    /*! \brief Cleanup this CSV file reader
     */
    ~QCsvFileReaderTemplate()
    {
      close();
    }

    QCsvFileReaderTemplate(const QCsvFileReaderTemplate &) = delete;
    QCsvFileReaderTemplate & operator=(const QCsvFileReaderTemplate &) = delete;
    QCsvFileReaderTemplate(QCsvFileReaderTemplate &&) = delete;
    QCsvFileReaderTemplate & operator=(QCsvFileReaderTemplate &&) = delete;

    /*! \brief Set the path to the file
     *
     * \pre \a filePath must not be empty
     * \pre This file reader must not be open
     * \sa isOpen()
     */
    void setFilePath(const QString & filePath)
    {
      Q_ASSERT( !filePath.isEmpty() );
      Q_ASSERT( !isOpen() );

      mFilePath = filePath;
    }

    /*! \brief Get the path to the file
     *
     * \sa setFilePath()
     */
    const QString & filePath() const noexcept
    {
      return mFilePath;
    }

    /*! \brief Set CSV settings
     *
     * \pre \a settings must be valid
     * \pre This file reader must not be open
     * \sa isOpen()
     */
    void setCsvSettings(const CsvParserSettings & settings) noexcept
    {
      Q_ASSERT( settings.isValid() );
      Q_ASSERT( !isOpen() );

//       mParser.setCsvSettings(settings);
    }

    /*! \brief Get CSV settings
     */
    const CsvParserSettings & csvSettings() const noexcept
    {
//       return mParser.csvSettings();
    }

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
     *
     * \todo Error handling has to be implemented
     */
    void open()
    {
      Q_ASSERT( !filePath().isEmpty() );

//       mFileStream.open(mFilePath);
//       if( mFileStream.fail() ){
//         const QString what = tr("open file '%1' failed").arg(mFilePath);
//         throw QFileOpenError(what);
//       }
// 
//       mFileIterator = boost::spirit::make_default_multi_pass( SourceIterator(mFileStream) );
    }

    /*! \brief Check if this file reader is open
     *
     * \sa open()
     */
    bool isOpen() const
    {
//       return mFileStream.is_open();
    }

    /*! \brief Check if this file reader is at end
     *
     * \pre This file reader must be open
     * \sa isOpen()
     */
    bool atEnd() const noexcept
    {
      Q_ASSERT( isOpen() );

//       return mFileIterator == sourceIteratorEnd();
    }

    /*! \brief Read a line from the CSV file
     *
     * \exception QCsvFileReadError
     * \pre This file reader must be open
     * \pre This file reader must not be at end
     * \sa isOpen()
     * \sa atEnd()
     */
    template<typename Record>
    Record readLine() const
    {
      Q_ASSERT( isOpen() );
      Q_ASSERT( !atEnd() );

//       return mParser.readLine<Record>( mFileIterator, sourceIteratorEnd() );
    }

    /*! \brief Read all lines from the CSV file
     *
     * \exception QCsvFileReadError
     * \pre This file reader must be open
     * \pre This file reader must not be at end (i.e. the file must not be empty)
     * \sa isOpen()
     * \sa atEnd()
     */
    template<typename RecordList>
    RecordList readAll() const
    {
      Q_ASSERT( isOpen() );
      Q_ASSERT( !atEnd() );

//       return RecordList();
    }

    /*! \brief Close this file reader
     */
    void close()
    {
//       mFileStream.close();
    }

   private:

//     static
//     MultiPassSourceIterator sourceIteratorEnd() noexcept
//     {
//       return boost::spirit::make_default_multi_pass( SourceIterator() );
//     }

//     MultiPassSourceIterator mFileIterator;
//     CsvParserTemplate<MultiPassSourceIterator> mParser;
//     std::ifstream mFileStream;
    QString mFilePath;

  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_QCSV_FILE_READER_TEMPLATE_H
