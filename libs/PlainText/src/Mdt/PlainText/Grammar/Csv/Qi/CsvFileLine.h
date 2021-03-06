/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_QI_CSV_FILE_LINE_H
#define MDT_PLAIN_TEXT_GRAMMAR_CSV_QI_CSV_FILE_LINE_H

#include "CsvRecord.h"
#include "Mdt/PlainText/CsvParserSettings.h"
#include <boost/spirit/include/qi.hpp>
#include <cassert>

namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{ namespace Qi{

  /*! \brief CSV file line rule
   *
   * \note Some part of this API documentation refers to following standards:
   *       \li CSV-1203 available here: https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw
   *       \li RFC 4180 available here: https://tools.ietf.org/html/rfc4180
   */
  template <typename SourceIterator, typename DestinationRecord>
  struct CsvFileLine : boost::spirit::qi::grammar<SourceIterator, DestinationRecord()>
  {
    /*! \brief Constructor
     *
     * \pre \a settings must be valid
     */
    CsvFileLine(const CsvParserSettings & settings) noexcept
     : CsvFileLine::base_type(mCsvFileLine, "CsvFileLine"),
       mRecord(settings)
    {
      assert( settings.isValid() );

      namespace qi = boost::spirit::qi;

      using qi::eol;

      nameRules();

      mCsvFileLine = mRecord >> -eol;

      BOOST_SPIRIT_DEBUG_NODE(mCsvFileLine);
    }

   private:

    void nameRules()
    {
      mCsvFileLine.name("CsvFileLine");
    }

    boost::spirit::qi::rule<SourceIterator, DestinationRecord()> mCsvFileLine;
    CsvRecord<SourceIterator, DestinationRecord> mRecord;
  };

}}}}} // namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{ namespace Qi{

#endif // #ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_QI_CSV_FILE_LINE_H
