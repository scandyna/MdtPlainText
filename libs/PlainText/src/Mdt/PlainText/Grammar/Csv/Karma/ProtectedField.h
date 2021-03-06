/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_KARMA_PROTECTED_FIELD_H
#define MDT_PLAIN_TEXT_GRAMMAR_CSV_KARMA_PROTECTED_FIELD_H

#include "SafeChar.h"
#include "Mdt/PlainText/CsvGeneratorSettings.h"
#include <boost/spirit/include/karma.hpp>
#include <cstdint>
#include <string>
#include <cassert>

// #include <boost/spirit/include/karma_char_.hpp>

namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{ namespace Karma{


  /*! \brief CSV protected field rule
   *
   * \note Some part of this API documentation refers to following standards:
   *       \li CSV-1203 available here: https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw
   *       \li RFC 4180 available here: https://tools.ietf.org/html/rfc4180
   */
  template <typename DestinationIterator, typename SourceString>
  struct ProtectedField : boost::spirit::karma::grammar<DestinationIterator, SourceString()>
  {
//     using Char = boost::spirit::char_encoding::unicode::char_type;
    using Char = uint32_t;
//     using Char = char;

    /*! \brief Constructor
     *
     * \pre \a settings must be valid
     */
    ProtectedField(const CsvGeneratorSettings & settings) noexcept
     : ProtectedField::base_type(mProtectedField, "ProtectedField"),
       mSafeChar(settings)
    {
      assert( settings.isValid() );

      namespace karma = boost::spirit::karma;

      using karma::lit;
      using boost::spirit::karma::unicode::char_;
      using boost::spirit::unicode::space;

      const char fieldSep = settings.fieldSeparator();
      const char fieldQuote = settings.fieldProtection();
      const bool addExp = settings.addExp();

      nameRules();

      if(addExp){
        mProtectedField = lit(fieldQuote) << lit('~') << mFieldPayload << lit(fieldQuote);
      }else{
        mProtectedField = lit(fieldQuote) << mFieldPayload << lit(fieldQuote);
      }

      mFieldPayload = +mAnychar;

      // Character collections
      mAnychar = mChar | char_(fieldSep) | (char_(fieldQuote) << lit(fieldQuote)) | space; // space matches space, CR, LF and other See std::isspace()
      mChar = mSafeChar | char_(0x20);  // 0x20 == SPACE char

      BOOST_SPIRIT_DEBUG_NODE(mProtectedField);
      BOOST_SPIRIT_DEBUG_NODE(mFieldPayload);
      BOOST_SPIRIT_DEBUG_NODE(mAnychar);
      BOOST_SPIRIT_DEBUG_NODE(mChar);
    }

   private:

    void nameRules()
    {
      mProtectedField.name("ProtectedField");
      mFieldPayload.name("FieldPayload");
      mAnychar.name("Anychar");
      mChar.name("Char");
    }

    boost::spirit::karma::rule<DestinationIterator, SourceString()> mProtectedField;
    boost::spirit::karma::rule<DestinationIterator, SourceString()> mFieldPayload;
    boost::spirit::karma::rule<DestinationIterator, Char()> mAnychar;
    boost::spirit::karma::rule<DestinationIterator, Char()> mChar;
    SafeChar<DestinationIterator, uint32_t> mSafeChar;
  };

}}}}} // namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{ namespace Karma{

#endif // #ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_KARMA_PROTECTED_FIELD_H
