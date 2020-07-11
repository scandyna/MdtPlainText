/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_RECORD_RULE_H
#define MDT_PLAIN_TEXT_GRAMMAR_CSV_RECORD_RULE_H

#include "FieldColumnRule.h"
#include "Mdt/PlainText/CsvParserSettings.h"
#include <boost/spirit/include/qi.hpp>
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
   * Neverthless, this implementation accepts empty fields,
   * as well as 1 column records.
   * To avoid empty records, the grammar becomes:
   * \code
   * Record = NonEmptyFieldColumn / ( FieldColumn *(COMMA FieldColumn) )
   * \endcode
   *
   * \note Some part of this API documentation refers to following standards:
   *       \li CSV-1203 available here: https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw
   *       \li RFC 4180 available here: https://tools.ietf.org/html/rfc4180
   */
  template <typename SourceIterator, typename DestinationRecord>
  struct RecordRule : boost::spirit::qi::grammar<SourceIterator, DestinationRecord()>
  {
    using StringType = typename DestinationRecord::value_type;

    /*! \brief Constructor
     *
     * \pre \a settings must be valid
     */
    RecordRule(const CsvParserSettings & settings) noexcept
     : RecordRule::base_type(mRecordPayload),
       mFieldColumn(settings)
    {
      assert( settings.isValid() );

      namespace qi = boost::spirit::qi;

      using qi::eol;
      using qi::lit;

      nameRules();

//       const char fieldSep = settings.fieldSeparator();

//       mRecordRule = mRecordPayload >> eol;
//       mRecordRule = mRecordPayload >> -eol; // RFC 4180 do not need a end of line in last line
//       mRecordPayload = mFieldColumn >> *(fieldSep >> mFieldColumn);
      mRecordPayload = mFieldColumn % lit( settings.fieldSeparator() );

      BOOST_SPIRIT_DEBUG_NODE(mRecordRule);
      BOOST_SPIRIT_DEBUG_NODE(mRecordPayload);
    }

   private:

    void nameRules()
    {
      mRecordRule.name("RecordRule");
      mRecordPayload.name("RecordPayload");
      mFieldColumn.name("FieldColumn");
    }

    boost::spirit::qi::rule<SourceIterator, DestinationRecord()> mRecordRule;
    boost::spirit::qi::rule<SourceIterator, DestinationRecord()> mRecordPayload;
    FieldColumnRule<SourceIterator, StringType> mFieldColumn;
  };

}}}} // namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{

#endif // #ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_RECORD_RULE_H
