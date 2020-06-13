/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_CSV_FILE_READER_H
#define MDT_PLAIN_TEXT_CSV_FILE_READER_H

#include "CsvParserSettings.h"
#include "FileOpenError.h"
#include "mdt_plaintext_export.h"
#include <vector>
#include <string>
#include <memory>

namespace Mdt{ namespace PlainText{

  class CsvFileReaderTemplate;

  /*! \brief CSV file reader
   *
   * Example of usage:
   * \code
   * Mdt::PlainText::CsvFileReader csvReader;
   *
   * csvReader.setFilePath("/some/path/to/file.csv");
   * csvReader.open();
   * while( !csvReader.atEnd() ){
   *   processRecord( csvReader.readLine() );
   * }
   * csvReader.close();
   * \endcode
   *
   * If you need a other output than std::vector<std::string>,
   * take a look at CsvFileReaderTemplate.
   *
   * \note Some part of this API documentation refers to following standards:
   *       \li CSV-1203 available here: https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw
   *       \li RFC 4180 available here: https://tools.ietf.org/html/rfc4180
   * \sa CsvFileReaderTemplate
   */
  class MDT_PLAINTEXT_EXPORT CsvFileReader
  {
   public:

    /*! \brief Construct a CSV file reader
     */
    CsvFileReader();

    /*! \brief Cleanup this CSV file reader
     */
    ~CsvFileReader();

    CsvFileReader(const CsvFileReader &) = delete;
    CsvFileReader & operator=(const CsvFileReader &) = delete;
    CsvFileReader(CsvFileReader &&) = delete;
    CsvFileReader & operator=(CsvFileReader &&) = delete;

    /*! \brief Set the path to the file
     *
     * \pre \a filePath must not be empty
     * \pre This file reader must not be open
     * \sa isOpen()
     */
    void setFilePath(const std::string & filePath);

    /*! \brief Get the path to the file
     *
     * \sa setFilePath()
     */
    const std::string & filePath() const noexcept;

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
     * \exception FileOpenError
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
     * \exception CsvFileReadError
     * \pre This file reader must be open
     * \sa isOpen()
     */
    std::vector<std::string> readLine() const;

    /*! \brief Read all lines from the CSV file
     *
     * \exception CsvFileReadError
     * \pre This file reader must be open
     * \sa isOpen()
     */
    std::vector< std::vector<std::string> > readAll() const;

    /*! \brief Close this file reader
     */
    void close();

   private:

    std::unique_ptr<CsvFileReaderTemplate> mImpl;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_CSV_FILE_READER_H
