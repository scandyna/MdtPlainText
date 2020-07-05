/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_RECORD_RULE_H
#define MDT_PLAIN_TEXT_GRAMMAR_CSV_RECORD_RULE_H

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
    /*! \brief Constructor
     *
     * \pre \a settings must be valid
     */
    RecordRule(const CsvParserSettings & settings) noexcept
     : RecordRule::base_type(mRecordRule)
    {
      assert( settings.isValid() );
    }

   private:

    boost::spirit::qi::rule<SourceIterator, DestinationRecord()> mRecordRule;
  };

}}}} // namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{

#endif // #ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_RECORD_RULE_H
