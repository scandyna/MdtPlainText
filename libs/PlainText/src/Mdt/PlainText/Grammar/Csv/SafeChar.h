/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_SAFE_CHAR_H
#define MDT_PLAIN_TEXT_GRAMMAR_CSV_SAFE_CHAR_H

#include "Mdt/PlainText/CsvParserSettings.h"
#include <boost/spirit/include/qi.hpp>
#include <cassert>
#include <string>

namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{


  /*! \brief SafeChar rule
   *
   *
   * \note Some part of this API documentation refers to following standards:
   *       \li CSV-1203 available here: https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw
   *       \li RFC 4180 available here: https://tools.ietf.org/html/rfc4180
   */
  template <typename SourceIterator, typename DestinationChar>
  struct SafeChar : boost::spirit::qi::grammar<SourceIterator, DestinationChar()>
  {
    /*! \brief Constructor
     *
     * \pre \a settings must be valid
     */
    SafeChar(const CsvParserSettings & settings) noexcept
     : SafeChar::base_type(mSafeChar)
    {
      assert( settings.isValid() );

      namespace qi = boost::spirit::qi;

      using boost::spirit::unicode::char_;

      const char fieldSep = settings.fieldSeparator();
      const char fieldQuote = settings.fieldProtection();

      nameRules();

      const std::string exclude = std::string("\n\t\r") + fieldSep + fieldQuote;
      mSafeChar = ~char_(exclude);

      BOOST_SPIRIT_DEBUG_NODE(mSafeChar);
    }

   private:

    void nameRules()
    {
      mSafeChar.name("SafeChar");
    }

    boost::spirit::qi::rule<SourceIterator, DestinationChar()> mSafeChar;
  };

}}}} // namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{

#endif // #ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_SAFE_CHAR_H
