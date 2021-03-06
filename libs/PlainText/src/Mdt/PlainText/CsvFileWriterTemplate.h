/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_CSV_FILE_WRITER_TEMPLATE_H
#define MDT_PLAIN_TEXT_CSV_FILE_WRITER_TEMPLATE_H

#include "FileOpenError.h"
#include "CsvFileWriteError.h"
#include "EndOfLine.h"
#include "CsvGeneratorSettings.h"
#include "FileWriteOpenMode.h"
#include "OpenFstream.h"
#include "mdt_plaintext_export.h"
#include <boost/spirit/include/karma.hpp>
#include <string>
#include <fstream>
#include <iterator>

namespace Mdt{ namespace PlainText{

  /*! \brief CSV file writer template
   *
   * CsvFileWriterTemplate implements the most part to write CSV files,
   * but let you choose the input containers.
   * In counterpart, it includes all the implementation,
   * which increases the compile time significantly.
   *
   * If you can use std::vector<std::string> as input records,
   * consider using CsvFileWriter.
   *
   * Here is a minimal example of a possible CSV file writer:
   * \code
   * using MyRecord = std::vector<std::string>;
   *
   * class MyCsvFileWriter
   * {
   *  public:
   *
   *   // All required public methods, constructors, destructor
   *
   *   void writeLine(cont MyRecord & record);
   *
   *  private:
   *
   *   std::unique_ptr<Mdt::PlainText::CsvFileWriterTemplate> mImpl;
   * };
   * \endcode
   *
   * The implementation of %writeLine():
   * \code
   * void MyCsvFileWriter::writeLine(const MyRecord & record)
   * {
   *   using DestinationIterator = CsvFileWriterTemplate::iterator;
   *
   *   // A boost Spirit Karma rule
   *   MyRecordRule<DestinationIterator, MyRecord> rule( csvSettings() );
   *
   *   mImpl->writeLine(record, rule);
   * }
   * \endcode
   *
   * \sa CsvFileWriter
   */
  class MDT_PLAINTEXT_EXPORT CsvFileWriterTemplate
  {
   public:

    /*! \brief STL iterator
     */
    using iterator = std::ostreambuf_iterator<char>;

    /*! \brief Construct a CSV file writer
     */
    CsvFileWriterTemplate() = default;

    /*! \brief Cleanup this CSV file writer
     */
    ~CsvFileWriterTemplate()
    {
      close();
    }

    CsvFileWriterTemplate(const CsvFileWriterTemplate &) = delete;
    CsvFileWriterTemplate & operator=(const CsvFileWriterTemplate &) = delete;
    CsvFileWriterTemplate(CsvFileWriterTemplate &&) = delete;
    CsvFileWriterTemplate & operator=(CsvFileWriterTemplate &&) = delete;

    /*! \brief Set the path to the file
     *
     * \pre \a filePath must not be empty
     * \pre This file writer must not be open
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
      assert( !filePath().empty() );

      openOfstream(mFileStream, mFilePath, mOpenMode);
    }

    /*! \brief Check if this file writer is open
     *
     * \sa open()
     */
    bool isOpen() const
    {
      return mFileStream.is_open();
    }

    /*! \brief Write a line to this CSV file
     *
     * \exception CsvFileWriteError
     * \pre This file writer must be open
     * \sa isOpen()
     */
    template<typename Record, typename Rule>
    void writeLine(const Record & record, const Rule & rule)
    {
      assert( isOpen() );

      iterator it(mFileStream);
      const bool ok = boost::spirit::karma::generate(it, rule, record);
      if(!ok){
        const std::string what = "writing a line in file '" + mFilePath + "' failed";
        throw CsvFileWriteError(what);
      }
    }

    /*! \brief Write a table to this CSV file
     *
     * \exception CsvFileWriteError
     * \pre This file writer must be open
     * \sa isOpen()
     */
    template<typename Table, typename Rule>
    void writeTable(const Table & table, const Rule & rule)
    {
      assert( isOpen() );

      iterator it(mFileStream);
      const bool ok = boost::spirit::karma::generate(it, rule, table);
      if(!ok){
        const std::string what = "writing table in file '" + mFilePath + "' failed";
        throw CsvFileWriteError(what);
      }
    }

    /*! \brief Close this file writer
     */
    void close()
    {
      mFileStream.close();
    }

   private:

    CsvGeneratorSettings mCsvSettings;
    FileWriteOpenMode mOpenMode;
    std::ofstream mFileStream;
    std::string mFilePath;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_CSV_FILE_WRITER_TEMPLATE_H
