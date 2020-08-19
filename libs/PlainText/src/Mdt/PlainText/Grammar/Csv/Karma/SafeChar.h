/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_KARMA_SAFE_CHAR_H
#define MDT_PLAIN_TEXT_GRAMMAR_CSV_KARMA_SAFE_CHAR_H

#include "Mdt/PlainText/CsvGeneratorSettings.h"
#include <boost/spirit/include/karma.hpp>
// #include <cstdint>
#include <string>
#include <cassert>

namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{ namespace Karma{

  /*! \brief CSV SafeChar rule
   *
   * \note Some part of this API documentation refers to following standards:
   *       \li CSV-1203 available here: https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw
   *       \li RFC 4180 available here: https://tools.ietf.org/html/rfc4180
   */
  template <typename DestinationIterator, typename SourceChar>
  struct SafeChar : boost::spirit::karma::grammar<DestinationIterator, SourceChar()>
  {
    /*! \brief Constructor
     *
     * \pre \a settings must be valid
     */
    SafeChar(const CsvGeneratorSettings & settings) noexcept
     : SafeChar::base_type(mSafeChar, "SafeChar")
    {
      assert( settings.isValid() );

      using boost::spirit::karma::unicode::char_;

      const char fieldSep = settings.fieldSeparator();
      const char fieldQuote = settings.fieldProtection();

      nameRules();

      const std::u32string exclude = std::u32string(U"\n\t\r ") + static_cast<char32_t>(fieldSep) + static_cast<char32_t>(fieldQuote);
      mSafeChar = ~char_(exclude);
//       mSafeChar = char_(0x21) | char_(0x23, 0x2B) | char_(0x2D, 0xFF);

      BOOST_SPIRIT_DEBUG_NODE(mSafeChar);
    }

   private:

    void nameRules()
    {
      mSafeChar.name("SafeChar");
    }

    boost::spirit::karma::rule<DestinationIterator, SourceChar()> mSafeChar;
  };

}}}}} // namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{ namespace Karma{

#endif // #ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_KARMA_SAFE_CHAR_H
