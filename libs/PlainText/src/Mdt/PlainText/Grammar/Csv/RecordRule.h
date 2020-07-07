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
     : RecordRule::base_type(mRecordRule),
       mFieldColumn(settings)
    {
      assert( settings.isValid() );

      namespace qi = boost::spirit::qi;

      using qi::eol;
      using qi::lit;

      nameRules();

      mRecordRule = mRecordPayload >> -eol; // RFC 4180 do not need a end of line in last line
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
