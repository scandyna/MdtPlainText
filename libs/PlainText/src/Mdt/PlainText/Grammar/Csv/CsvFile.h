/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_CSV_FILE_H
#define MDT_PLAIN_TEXT_GRAMMAR_CSV_CSV_FILE_H

#include "CsvRecord.h"
#include "Mdt/PlainText/CsvParserSettings.h"
#include <boost/spirit/include/qi.hpp>
#include <cassert>

namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{

  /*! \brief CSV file rule
   *
   * CSV-1203 describes a CSV file as:
   * \code
   * csvfile = csvheader *datarecord [EOF]
   * csvheader = csvrecord
   * datarecord = csvrecord
   * csvrecord = recordpayload EOR
   * \endcode
   *
   * That means that each record MUST have a EOR (end of record),
   * and a file requires at least 1 record, which is the header.
   *
   *
   * \note Some part of this API documentation refers to following standards:
   *       \li CSV-1203 available here: https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw
   *       \li RFC 4180 available here: https://tools.ietf.org/html/rfc4180
   */
  template <typename SourceIterator, typename DestinationTable>
  struct CsvFile : boost::spirit::qi::grammar<SourceIterator, DestinationTable()>
  {
    using Record = typename DestinationTable::value_type;

    /*! \brief Constructor
     *
     * \pre \a settings must be valid
     */
    CsvFile(const CsvParserSettings & settings) noexcept
     : CsvFile::base_type(mCsvFile, "CsvFile"),
       mRecord(settings)
    {
      assert( settings.isValid() );

      namespace qi = boost::spirit::qi;

      using qi::eol;

      nameRules();

      mCsvFile = (mRecord % eol) >> -eol;

      BOOST_SPIRIT_DEBUG_NODE(mCsvFile);
    }

   private:

    void nameRules()
    {
      mCsvFile.name("CsvFile");
      mRecord.name("Record");
    }

    boost::spirit::qi::rule<SourceIterator, DestinationTable()> mCsvFile;
    CsvRecord<SourceIterator, Record> mRecord;
  };

}}}} // namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{

#endif // #ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_CSV_FILE_H
