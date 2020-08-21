/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_KARMA_CSV_RECORD_H
#define MDT_PLAIN_TEXT_GRAMMAR_CSV_KARMA_CSV_RECORD_H

#include "FieldColumn.h"
#include "Mdt/PlainText/CsvGeneratorSettings.h"
#include "Mdt/PlainText/EndOfLine.h"
#include <boost/spirit/include/karma.hpp>
#include <cassert>

namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{ namespace Karma{

  /*! \brief CSV record rule
   *
   * \note Some part of this API documentation refers to following standards:
   *       \li CSV-1203 available here: https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw
   *       \li RFC 4180 available here: https://tools.ietf.org/html/rfc4180
   */
  template <typename DestinationIterator, typename SourceRecord>
  struct CsvRecord : boost::spirit::karma::grammar<DestinationIterator, SourceRecord()>
  {
    using SourceString = typename SourceRecord::value_type;

    /*! \brief Constructor
     *
     * \pre \a settings must be valid
     */
    CsvRecord(const CsvGeneratorSettings & settings) noexcept
     : CsvRecord::base_type(mCsvRecord, "CsvRecord"),
       mFieldColumn(settings)
    {
      assert( settings.isValid() );

      using boost::spirit::lit;

      const char fieldSep = settings.fieldSeparator();
      EndOfLine endOfLine = settings.endOfLine();

      if( endOfLine == EndOfLine::Native ){
        endOfLine = Mdt::PlainText::nativeEndOfLine();
      }
      switch(endOfLine){
        case EndOfLine::Lf:
          mCsvRecord = mRecordPayload << lit('\n');
          break;
        case EndOfLine::CrLf:
          mCsvRecord = mRecordPayload << lit('\r') << lit('\n');
          break;
        case EndOfLine::Cr:
          mCsvRecord = mRecordPayload << lit('\r');
          break;
        default:
          break;
      }

      mRecordPayload = mFieldColumn % lit(fieldSep);

      BOOST_SPIRIT_DEBUG_NODE(mCsvRecord);
      BOOST_SPIRIT_DEBUG_NODE(mRecordPayload);
    }

   private:

    boost::spirit::karma::rule<DestinationIterator, SourceRecord()> mCsvRecord;
    boost::spirit::karma::rule<DestinationIterator, SourceRecord()> mRecordPayload;
    FieldColumn<DestinationIterator, SourceString> mFieldColumn;
  };

}}}}} // namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{ namespace Karma{

#endif // #ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_KARMA_CSV_RECORD_H
