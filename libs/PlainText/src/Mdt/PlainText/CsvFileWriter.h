/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_CSV_FILE_WRITER_H
#define MDT_PLAIN_TEXT_CSV_FILE_WRITER_H

#include "FileOpenError.h"
#include "EndOfLine.h"
#include "CsvGeneratorSettings.h"
#include "FileWriteOpenMode.h"
#include "mdt_plaintext_export.h"
#include <string>
#include <memory>

namespace Mdt{ namespace PlainText{

  class CsvFileWriterTemplate;

  /*! \brief CSV file writer
   *
   * Example of usage:
   * \code
   * Mdt::PlainText::CsvFileWriter csvWriter;
   *
   * csvWriter.setFilePath("/some/path/to/file.csv");
   * csvWriter.open();
   * csvWriter.appendRecord({"A","B","C"});
   * \endcode
   */
  class MDT_PLAINTEXT_EXPORT CsvFileWriter
  {
   public:

    /*! \brief Construct a CSV file writer
     */
    CsvFileWriter();

    /*! \brief Cleanup this CSV file writer
     */
    ~CsvFileWriter();

    CsvFileWriter(const CsvFileWriter &) = delete;
    CsvFileWriter & operator=(const CsvFileWriter &) = delete;
    CsvFileWriter(CsvFileWriter &&) = delete;
    CsvFileWriter & operator=(CsvFileWriter &&) = delete;

    /*! \brief Set the path to the file
     *
     * \pre \a filePath must not be empty
     * \pre This file writer must not be open
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

    std::unique_ptr<CsvFileWriterTemplate> mImpl;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_CSV_FILE_WRITER_H
