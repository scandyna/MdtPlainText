/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_CSV_FILE_READER_TEMPLATE_H
#define MDT_PLAIN_TEXT_CSV_FILE_READER_TEMPLATE_H

#include "CsvParserSettings.h"
#include "FileOpenError.h"
#include "CsvFileReadError.h"
#include "OpenFstream.h"
#include "mdt_plaintext_export.h"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <string>
#include <cassert>
#include <fstream>
#include <iterator>

namespace Mdt{ namespace PlainText{

  /*! \brief CSV file reader template
   *
   * CsvFileReaderTemplate implements the most part to read CSV files,
   * but let you choose the output containers.
   * In counterpart, it includes all the implementation,
   * which increases the compile time significantly.
   *
   * If you can use std::vector<std::string> as output records,
   * consider using CsvFileReader.
   *
   * Here is a minimal example of a possible CSV file reader:
   * \code
   * using MyRecord = std::vector<std::string>;
   *
   * class MyCsvFileReader
   * {
   *  public:
   *
   *   // All required public methods, constructors, destructor
   *
   *   MyRecord readLine() const;
   *
   *  private:
   *
   *   std::unique_ptr<Mdt::PlainText::CsvFileReaderTemplate> mImpl;
   * };
   * \endcode
   *
   * The implementation of %readLine():
   * \code
   * MyRecord MyCsvFileReader::readLine() const
   * {
   *   using SourceIterator = CsvFileReaderTemplate::const_iterator;
   *
   *   MyRecordRule<SourceIterator, MyRecord> rule( csvSettings() );
   *
   *   return mImpl->readLine<MyRecord>(rule);
   * }
   * \endcode
   *
   * \sa CsvFileReader
   */
  class MDT_PLAINTEXT_EXPORT CsvFileReaderTemplate
  {
    using FileIterator = std::istreambuf_iterator<char>;

   public:

    /*! \brief STL const iterator
     */
    using const_iterator = boost::spirit::multi_pass<FileIterator>;

    /*! \brief Construct a CSV file reader
     */
    CsvFileReaderTemplate() = default;

    /*! \brief Cleanup this CSV file reader
     */
    ~CsvFileReaderTemplate()
    {
      close();
    }

    CsvFileReaderTemplate(const CsvFileReaderTemplate &) = delete;
    CsvFileReaderTemplate & operator=(const CsvFileReaderTemplate &) = delete;
    CsvFileReaderTemplate(CsvFileReaderTemplate &&) = delete;
    CsvFileReaderTemplate & operator=(CsvFileReaderTemplate &&) = delete;

    /*! \brief Set the path to the file
     *
     * \pre \a filePath must not be empty
     * \pre This file reader must not be open
     * \sa isOpen()
     */
    void setFilePath(const std::string & filePath)
    {
      assert( !filePath.empty() );
      assert( !isOpen() );

      mFilePath = filePath;
    }

    /*! \brief Get the path to the file
     *
     * \sa setFilePath()
     */
    const std::string & filePath() const noexcept
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
      assert( settings.isValid() );
      assert( !isOpen() );

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
     * \exception FileOpenError
     * \pre A path to a file must have been set
     * \sa setFilePath()
     * \sa close()
     *
     * \todo Error handling has to be implemented
     */
    void open()
    {
      assert( !filePath().empty() );

      openIfstream(mFileStream, mFilePath);

      mSourceIterator = boost::spirit::make_default_multi_pass( FileIterator(mFileStream) );
    }

    /*! \brief Check if this file reader is open
     *
     * \sa open()
     */
    bool isOpen() const
    {
      return mFileStream.is_open();
    }

    /*! \brief Check if this file reader is at end
     *
     * \pre This file reader must be open
     * \sa isOpen()
     */
    bool atEnd() const noexcept
    {
      assert( isOpen() );

      return mSourceIterator == sourceIteratorEnd();
    }

    /*! \brief Read a line from the CSV file
     *
     * \exception CsvFileReadError
     * \pre This file reader must be open
     * \pre This file reader must not be at end
     * \sa isOpen()
     * \sa atEnd()
     */
    template<typename Record, typename Rule>
    Record readLine(const Rule & rule)
    {
      assert( isOpen() );
      assert( !atEnd() );

      Record record;
      const auto last = sourceIteratorEnd();

      const bool ok = boost::spirit::qi::parse(mSourceIterator, last, rule, record);
      if(!ok){
        const std::string what = "reading file '" + mFilePath + "' failed";
        throw CsvFileReadError(what);
      }

      return record;
    }

    /*! \brief Read all lines from the CSV file
     *
     * \exception CsvFileReadError
     * \pre This file reader must be open
     * \pre This file reader must not be at end (i.e. the file must not be empty)
     * \sa isOpen()
     * \sa atEnd()
     */
    template<typename RecordList, typename Rule>
    RecordList readAll(const Rule & rule)
    {
      assert( isOpen() );
      assert( !atEnd() );

      RecordList table;
      const auto last = sourceIteratorEnd();

      const bool ok = boost::spirit::qi::parse(mSourceIterator, last, rule, table);
      if(!ok){
        const std::string what = "reading file '" + mFilePath + "' failed";
        throw CsvFileReadError(what);
      }

      return table;
    }

    /*! \brief Close this file reader
     */
    void close()
    {
      mFileStream.close();
    }

   private:

    static
    const_iterator sourceIteratorEnd() noexcept
    {
      return boost::spirit::make_default_multi_pass( FileIterator() );
    }

    const_iterator mSourceIterator;
    std::ifstream mFileStream;
    std::string mFilePath;
    CsvParserSettings mCsvSettings;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_CSV_FILE_READER_TEMPLATE_H
