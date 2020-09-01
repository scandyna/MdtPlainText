/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_KARMA_CSV_FILE_H
#define MDT_PLAIN_TEXT_GRAMMAR_CSV_KARMA_CSV_FILE_H

#include "CsvRecord.h"
#include "Mdt/PlainText/CsvGeneratorSettings.h"
#include <boost/spirit/include/karma.hpp>
#include <cassert>

namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{ namespace Karma{

  /*! \brief CSV file rule
   *
   * \note Some part of this API documentation refers to following standards:
   *       \li CSV-1203 available here: https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw
   *       \li RFC 4180 available here: https://tools.ietf.org/html/rfc4180
   */
  template <typename DestinationIterator, typename SourceTable>
  struct CsvFile : boost::spirit::karma::grammar<DestinationIterator, SourceTable()>
  {
    /*! \brief Constructor
     *
     * \pre \a settings must be valid
     */
    CsvFile(const CsvGeneratorSettings & settings) noexcept
     : CsvFile::base_type(mCsvFile, "CsvFile"),
       mCsvRecord(settings)
    {
      assert( settings.isValid() );

      mCsvFile = +mCsvRecord;

      BOOST_SPIRIT_DEBUG_NODE(mCsvFile);
    }

   private:

    using SourceRecord = typename SourceTable::value_type;

    boost::spirit::karma::rule<DestinationIterator, SourceTable()> mCsvFile;
    CsvRecord<DestinationIterator, SourceRecord> mCsvRecord;
  };

}}}}} // namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{ namespace Karma{

#endif // #ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_KARMA_CSV_FILE_H
