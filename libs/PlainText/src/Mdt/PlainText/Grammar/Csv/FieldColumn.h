/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_FIELD_COLUMN_H
#define MDT_PLAIN_TEXT_GRAMMAR_CSV_FIELD_COLUMN_H

#include "UnprotectedField.h"
#include "Mdt/PlainText/CsvParserSettings.h"
#include <boost/spirit/include/qi.hpp>
#include <cstdint>
#include <cassert>

namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{

  /*! \brief CSV field column rule
   *
   * \note Some part of this API documentation refers to following standards:
   *       \li CSV-1203 available here: https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw
   *       \li RFC 4180 available here: https://tools.ietf.org/html/rfc4180
   */
  template <typename SourceIterator, typename DestinationString>
  struct FieldColumn : boost::spirit::qi::grammar<SourceIterator, DestinationString()>
  {
    using CharType = uint32_t;

    /*! \brief Constructor
     *
     * \pre \a settings must be valid
     */
    FieldColumn(const CsvParserSettings & settings) noexcept
     : FieldColumn::base_type(mFieldColumn),
       mUnprotectedField(settings)
    {
      assert( settings.isValid() );

      namespace qi = boost::spirit::qi;

      using qi::lit;
      using boost::spirit::unicode::char_;
      using boost::spirit::unicode::space;

      const char fieldSep = settings.fieldSeparator();
      const char fieldQuote = settings.fieldProtection();
      const bool parseExp = settings.parseExp();

      nameRules();

      mFieldColumn = mProtectedField | mUnprotectedField;
      if(parseExp){
        mProtectedField = lit(fieldQuote) >> -lit('~') >> mFieldPayload >> lit(fieldQuote);
      }else{
        mProtectedField = lit(fieldQuote) >> mFieldPayload >> lit(fieldQuote);
      }
      mFieldPayload = *mAnychar;
      // Character collections
      mAnychar = mChar | char_(fieldSep) | (char_(fieldQuote) >> lit(fieldQuote)) | space; // space matches space, CR, LF and other See std::isspace()
      mChar = mSafechar | char_(0x20);  // 0x20 == SPACE char
      const std::string exclude = std::string("\n\t\r") + fieldSep + fieldQuote;
      mSafechar = ~char_(exclude);

      BOOST_SPIRIT_DEBUG_NODE(mFieldColumn);
      BOOST_SPIRIT_DEBUG_NODE(mProtectedField);
      BOOST_SPIRIT_DEBUG_NODE(mFieldPayload);
      BOOST_SPIRIT_DEBUG_NODE(mAnychar);
      BOOST_SPIRIT_DEBUG_NODE(mChar);
      BOOST_SPIRIT_DEBUG_NODE(mSafechar);
    }

   private:

    void nameRules()
    {
      mFieldColumn.name("FieldColumn");
      mProtectedField.name("ProtectedField");
      mFieldPayload.name("FieldPayload");
      mAnychar.name("Anychar");
      mChar.name("Char");
      mSafechar.name("Safechar");
    }

    boost::spirit::qi::rule<SourceIterator, DestinationString()> mFieldColumn;
    boost::spirit::qi::rule<SourceIterator, DestinationString()> mProtectedField;
    UnprotectedField<SourceIterator, DestinationString> mUnprotectedField;
    boost::spirit::qi::rule<SourceIterator, DestinationString()> mFieldPayload;
    boost::spirit::qi::rule<SourceIterator, CharType()> mAnychar;
    boost::spirit::qi::rule<SourceIterator, CharType()> mChar;
    boost::spirit::qi::rule<SourceIterator, CharType()> mSafechar;
  };

}}}} // namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{

#endif // #ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_FIELD_COLUMN_H
