/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_CSV_RECORD_H
#define MDT_PLAIN_TEXT_GRAMMAR_CSV_CSV_RECORD_H

#include "FieldColumn.h"
#include "NonEmptyFieldColumn.h"
#include "Mdt/PlainText/CsvParserSettings.h"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <cassert>

namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{

  /*! \brief CSV record rule
   *
   * CSV-1203 describes a CSV record as:
   * \code
   * csvrecord = recordpayload EOR
   * recordpayload = fieldcolumn COMMA fieldcolumn *(COMMA fieldcolumn)
   * \endcode
   * This means that a record must have at least 2 columns,
   * and it must be terminated by a EOR (end of record)
   *
   * RFC 4180 describes a CSV record as:
   * \code
   * record = field *(COMMA field)
   * \endcode
   * That means that a record must have at least 1 column.
   *
   * A empty record has no meaning, and should not be allowed.
   * Nevertheless, this implementation accepts empty fields,
   * as well as 1 column records.
   * To avoid empty records, the grammar becomes:
   * \code
   * CsvRecord = RecordPayload / NonEmptyFieldColumn
   * RecordPayload = FieldColumn *(COMMA FieldColumn)
   * \endcode
   *
   * \note Some part of this API documentation refers to following standards:
   *       \li CSV-1203 available here: https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw
   *       \li RFC 4180 available here: https://tools.ietf.org/html/rfc4180
   */
  template <typename SourceIterator, typename DestinationRecord>
  struct CsvRecord : boost::spirit::qi::grammar<SourceIterator, DestinationRecord()>
  {
    using StringType = typename DestinationRecord::value_type;

    /*! \brief Constructor
     *
     * \pre \a settings must be valid
     */
    CsvRecord(const CsvParserSettings & settings) noexcept
     : CsvRecord::base_type(mCsvRecord, "CsvRecord"),
       mNonEmptyFieldColumn(settings),
       mFieldColumn(settings)
    {
      assert( settings.isValid() );

      namespace qi = boost::spirit::qi;

      using qi::eol;
      using qi::lit;
      using qi::_val;
      using qi::_1;
      using boost::phoenix::push_back;

      const char fieldSep = settings.fieldSeparator();

      nameRules();

      /*
       * Why we use semantic actions here
       *
       * When using automatic attributes propagation,
       * attributes are propagated despite a parser will eventually fail.
       * For example, parsing "ABC":
       *  - RecordPayload will parse and propagate attributes
       *  - RecordPayload fails
       *  - NonEmptyFieldColumn propagates attributes
       *  - The result is a record that contains [ABC,ABC]
       *
       * Semantic actions are only called when a parser succeeds.
       */
      mCsvRecord = mRecordPayload[_val = _1] | mNonEmptyFieldColumn[push_back(_val, _1)];
      mRecordPayload = mFieldColumn >> lit(fieldSep) >> ( mFieldColumn % lit(fieldSep) );

      BOOST_SPIRIT_DEBUG_NODE(mCsvRecord);
      BOOST_SPIRIT_DEBUG_NODE(mRecordPayload);
    }

   private:

    void nameRules()
    {
      mCsvRecord.name("CsvRecord");
      mRecordPayload.name("RecordPayload");
    }

    boost::spirit::qi::rule<SourceIterator, DestinationRecord()> mCsvRecord;
    boost::spirit::qi::rule<SourceIterator, DestinationRecord()> mRecordPayload;
    NonEmptyFieldColumn<SourceIterator, StringType> mNonEmptyFieldColumn;
    FieldColumn<SourceIterator, StringType> mFieldColumn;
  };

}}}} // namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{

#endif // #ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_CSV_RECORD_H
