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
#include "QCsvFileReadError.h"
#include "QTextCodecNotFoundError.h"
#include "BoostSpiritQTextFileInputConstIterator.h"
#include "BoostSpiritQStringContainer.h"
#include "Mdt/PlainText/CsvParserSettings.h"
#include "mdt_plaintext_qtcore_export.h"
#include <QByteArray>
#include <QString>
#include <QObject>
#include <QFile>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>

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
   *   using SourceIterator = QCsvFileReaderTemplate::const_iterator;
   *
   *   MyRecordRule<SourceIterator, MyRecord> rule( csvSettings() );
   *
   *   return mImpl->readLine<MyRecord>(rule);
   * }
   * \endcode
   *
   * \sa QCsvFileReader
   */
  class MDT_PLAINTEXT_QTCORE_EXPORT QCsvFileReaderTemplate : public QObject
  {
    Q_OBJECT

   public:

    /*! \brief STL const iterator
     */
    using const_iterator = boost::spirit::multi_pass<BoostSpiritQTextFileInputConstIterator>;

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
      Q_ASSERT( !isOpen() );

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
     * \pre This file reader must not be open
     * \sa isOpen()
     */
    void setCsvSettings(const CsvParserSettings & settings) noexcept
    {
      Q_ASSERT( settings.isValid() );
      Q_ASSERT( !isOpen() );

      mCsvSettings = settings;
    }

    /*! \brief Get CSV settings
     */
    const CsvParserSettings & csvSettings() const noexcept
    {
      return mCsvSettings;
    }

    /*! \brief Open this CSV file reader
     *
     * If this file reader is allready open,
     * it will be closed first().
     *
     * Open the file set with setFilePath().
     *
     * \exception QFileOpenError
     * \exception QTextCodecNotFoundError
     * \pre A path to a file must have been set
     * \sa setFilePath()
     * \sa close()
     */
    void open()
    {
      Q_ASSERT( !filePath().isEmpty() );

      if( !mFile.open(QIODevice::ReadOnly | QIODevice::Text) ){
        const QString what = tr("open file '%1' failed").arg(filePath());
        throw QFileOpenError(what);
      }

      try{
        mSourceIterator = boost::spirit::make_default_multi_pass( BoostSpiritQTextFileInputConstIterator(&mFile, mFileEncoding) );
      }catch(const QTextCodecNotFoundError & error){
        close();
        throw error;
      }
    }

    /*! \brief Check if this file reader is open
     *
     * \sa open()
     */
    bool isOpen() const
    {
      return mFile.isOpen();
    }

    /*! \brief Check if this file reader is at end
     *
     * \pre This file reader must be open
     * \sa isOpen()
     */
    bool atEnd() const noexcept
    {
      Q_ASSERT( isOpen() );

      return mSourceIterator == sourceIteratorEnd();
    }

    /*! \brief Read a line from the CSV file
     *
     * \exception QCsvFileReadError
     * \pre This file reader must be open
     * \pre This file reader must not be at end
     * \sa isOpen()
     * \sa atEnd()
     */
    template<typename Record, typename Rule>
    Record readLine(const Rule & rule)
    {
      Q_ASSERT( isOpen() );
      Q_ASSERT( !atEnd() );

      Record record;
      const auto last = sourceIteratorEnd();

      const bool ok = boost::spirit::qi::parse(mSourceIterator, last, rule, record);
      if(!ok){
        const QString what = tr("reading file %1 failed").arg(filePath());
        throw QCsvFileReadError(what);
      }

      return record;
    }

    /*! \brief Read all lines from the CSV file
     *
     * \exception QCsvFileReadError
     * \pre This file reader must be open
     * \pre This file reader must not be at end (i.e. the file must not be empty)
     * \sa isOpen()
     * \sa atEnd()
     */
    template<typename RecordList, typename Rule>
    RecordList readAll(const Rule & rule)
    {
      Q_ASSERT( isOpen() );
      Q_ASSERT( !atEnd() );

      RecordList table;
      const auto last = sourceIteratorEnd();

      const bool ok = boost::spirit::qi::parse(mSourceIterator, last, rule, table);
      if(!ok){
        const QString what = tr("reading file %1 failed").arg(filePath());
        throw QCsvFileReadError(what);
      }

      return table;
    }

    /*! \brief Close this file reader
     */
    void close()
    {
      mFile.close();
    }

   private:

    static
    const_iterator sourceIteratorEnd() noexcept
    {
      return boost::spirit::make_default_multi_pass( BoostSpiritQTextFileInputConstIterator() );
    }

    const_iterator mSourceIterator;
    QFile mFile;
    QByteArray mFileEncoding = "UTF-8";
    CsvParserSettings mCsvSettings;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_QCSV_FILE_READER_TEMPLATE_H
