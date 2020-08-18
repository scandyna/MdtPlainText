/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_NON_EMPTY_UNPROTECTED_FIELD_H
#define MDT_PLAIN_TEXT_GRAMMAR_CSV_NON_EMPTY_UNPROTECTED_FIELD_H

#include "Char.h"
#include "Mdt/PlainText/CsvParserSettings.h"
#include <boost/spirit/include/qi.hpp>
#include <cstdint>
#include <cassert>

namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{

  /*! \brief CSV non empty unprotected field rule
   *
   * CSV-1203 states at §3.4 that a field column should not have any leading or trailing white spaces.
   * RFC 4180 does not require this constraint.
   *
   * To be able to parse contents that do not completely conform to CSV-1203,
   * the leading and trailing white spaces are tolerated here.
   * (Note also that implementing the CSV-1203 rawfieldpayload could be complex in PEG).
   *
   * \note Some part of this API documentation refers to following standards:
   *       \li CSV-1203 available here: https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw
   *       \li RFC 4180 available here: https://tools.ietf.org/html/rfc4180
   */
  template <typename SourceIterator, typename DestinationString>
  struct NonEmptyUnprotectedField : boost::spirit::qi::grammar<SourceIterator, DestinationString()>
  {
    /*! \brief Constructor
     *
     * \pre \a settings must be valid
     */
    NonEmptyUnprotectedField(const CsvParserSettings & settings) noexcept
     : NonEmptyUnprotectedField::base_type(mNonEmptyUnprotectedField, "NonEmptyUnprotectedField"),
       mChar(settings)
    {
      assert( settings.isValid() );

      namespace qi = boost::spirit::qi;

      using qi::lit;

      const bool parseExp = settings.parseExp();

      if(parseExp){
        mNonEmptyUnprotectedField = -lit('~') >> +mChar;
      }else{
        mNonEmptyUnprotectedField = +mChar;
      }

      BOOST_SPIRIT_DEBUG_NODE(mNonEmptyUnprotectedField);
    }

   private:

    boost::spirit::qi::rule<SourceIterator, DestinationString()> mNonEmptyUnprotectedField;
    Char<SourceIterator, uint32_t> mChar;
  };

}}}} // namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{

#endif // #ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_NON_EMPTY_UNPROTECTED_FIELD_H
