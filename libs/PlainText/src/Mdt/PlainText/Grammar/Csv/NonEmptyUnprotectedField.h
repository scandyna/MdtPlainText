/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_NON_EMPTY_UNPROTECTED_FIELD_H
#define MDT_PLAIN_TEXT_GRAMMAR_CSV_NON_EMPTY_UNPROTECTED_FIELD_H

#include "SafeChar.h"
#include "Mdt/PlainText/CsvParserSettings.h"
#include <boost/spirit/include/qi.hpp>
#include <cstdint>
#include <cassert>

namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{

  /*! \brief CSV non empty unprotected field rule
   *
   * \note Some part of this API documentation refers to following standards:
   *       \li CSV-1203 available here: https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw
   *       \li RFC 4180 available here: https://tools.ietf.org/html/rfc4180
   */
  template <typename SourceIterator, typename DestinationString>
  struct NonEmptyUnprotectedField : boost::spirit::qi::grammar<SourceIterator, DestinationString()>
  {
    using Char = uint32_t;

    /*! \brief Constructor
     *
     * \pre \a settings must be valid
     */
    NonEmptyUnprotectedField(const CsvParserSettings & settings) noexcept
     : NonEmptyUnprotectedField::base_type(mNonEmptyUnprotectedField),
       mSafeChar(settings)
    {
      assert( settings.isValid() );

      namespace qi = boost::spirit::qi;

      using qi::lit;
      using boost::spirit::unicode::char_;

      const bool parseExp = settings.parseExp();

      nameRules();

      if(parseExp){
        mNonEmptyUnprotectedField = -lit('~') >> ( +mSafeChar | (mSafeChar >> *char_ >> mSafeChar) );
      }else{
        mNonEmptyUnprotectedField = +mSafeChar | (mSafeChar >> *char_ >> mSafeChar);
      }

      BOOST_SPIRIT_DEBUG_NODE(mNonEmptyUnprotectedField);
    }

   private:

    void nameRules()
    {
      mNonEmptyUnprotectedField.name("NonEmptyUnprotectedField");
    }

    boost::spirit::qi::rule<SourceIterator, DestinationString()> mNonEmptyUnprotectedField;
    SafeChar<SourceIterator, Char> mSafeChar;
  };

}}}} // namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{

#endif // #ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_NON_EMPTY_UNPROTECTED_FIELD_H
