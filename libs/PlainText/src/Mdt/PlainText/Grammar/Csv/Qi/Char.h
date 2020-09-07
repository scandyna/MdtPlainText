/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_QI_CHAR_H
#define MDT_PLAIN_TEXT_GRAMMAR_CSV_QI_CHAR_H

#include "SafeChar.h"
#include "Mdt/PlainText/CsvParserSettings.h"
#include <boost/spirit/include/qi.hpp>
#include <cassert>

namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{ namespace Qi{

  /*! \brief Char rule
   *
   *
   * \note Some part of this API documentation refers to following standards:
   *       \li CSV-1203 available here: https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw
   *       \li RFC 4180 available here: https://tools.ietf.org/html/rfc4180
   */
  template <typename SourceIterator, typename DestinationChar>
  struct Char : boost::spirit::qi::grammar<SourceIterator, DestinationChar()>
  {
    /*! \brief Constructor
     *
     * \pre \a settings must be valid
     */
    Char(const CsvParserSettings & settings) noexcept
     : Char::base_type(mChar, "Char"),
       mSafeChar(settings)
    {
      assert( settings.isValid() );

      using boost::spirit::unicode::char_;

      mChar = mSafeChar | char_(' ');

      BOOST_SPIRIT_DEBUG_NODE(mChar);
    }

   private:

    boost::spirit::qi::rule<SourceIterator, DestinationChar()> mChar;
    SafeChar<SourceIterator, DestinationChar> mSafeChar;
  };

}}}}} // namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{ namespace Qi{

#endif // #ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_QI_CHAR_H
