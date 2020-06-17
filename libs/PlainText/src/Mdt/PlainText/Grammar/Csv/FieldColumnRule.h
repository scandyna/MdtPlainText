/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_FIELD_COLUMN_RULE_H
#define MDT_PLAIN_TEXT_GRAMMAR_CSV_FIELD_COLUMN_RULE_H

#include "Mdt/PlainText/CsvParserSettings.h"
#include <boost/spirit/include/qi.hpp>
#include <cassert>

namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{

  /*! \brief CSV field column rule
   */
  template <typename SourceIterator, typename DestinationData>
  struct FieldColumnRule : boost::spirit::qi::grammar<SourceIterator, DestinationData()>
  {
    using CharType = typename DestinationData::value_type;

    /*! \brief Constructor
     *
     * \pre \a settings must be valid
     */
    FieldColumnRule(const CsvParserSettings & settings) noexcept
     : FieldColumnRule::base_type(mFieldColumnRule)
    {
      assert( settings.isValid() );

      namespace qi = boost::spirit::qi;

      using qi::lit;
      using qi::eol;
      using boost::spirit::standard::char_;
      using boost::spirit::standard::space;
//       using boost::spirit::standard_wide::char_;
//       using boost::spirit::standard_wide::space;

      const char fieldSep = settings.fieldSeparator();
      const char fieldQuote = settings.fieldProtection();
      const bool parseExp = settings.parseExp();

      nameRules();

      mFieldColumnRule = mProtectedField | mUnprotectedField;
      if(parseExp){
        mProtectedField = lit(fieldQuote) >> -lit('~') >> mFieldPayload >> lit(fieldQuote);
        mUnprotectedField = -lit('~') >> mRawFieldPayload;
      }else{
        mProtectedField = lit(fieldQuote) >> mFieldPayload >> lit(fieldQuote);
        mUnprotectedField = -char_('~') >> mRawFieldPayload; // mUnprotectedField = mRawFieldPayload causes runtime exception
      }
      mFieldPayload = *mAnychar;
      mRawFieldPayload = *mSafechar | (mSafechar >> *char_ >> mSafechar);
      // Character collections
      mAnychar = mChar | char_(fieldSep) | (char_(fieldQuote) >> lit(fieldQuote)) | space; // space matches space, CR, LF and other See std::isspace()
      mChar = mSafechar | char_(0x20);  // 0x20 == SPACE char
      std::string exclude = std::string("\n\t\r") + fieldSep + fieldQuote;
      mSafechar = ~char_(exclude);

      BOOST_SPIRIT_DEBUG_NODE(mFieldColumnRule);
      BOOST_SPIRIT_DEBUG_NODE(mRawFieldPayload);
      BOOST_SPIRIT_DEBUG_NODE(mProtectedField);
      BOOST_SPIRIT_DEBUG_NODE(mUnprotectedField);
      BOOST_SPIRIT_DEBUG_NODE(mFieldPayload);
      BOOST_SPIRIT_DEBUG_NODE(mRawFieldPayload);
      BOOST_SPIRIT_DEBUG_NODE(mAnychar);
      BOOST_SPIRIT_DEBUG_NODE(mChar);
      BOOST_SPIRIT_DEBUG_NODE(mSafechar);
    }

   private:

    void nameRules()
    {
      mFieldColumnRule.name("FieldColumnRule");
      mProtectedField.name("ProtectedField");
      mUnprotectedField.name("UnprotectedField");
      mFieldPayload.name("FieldPayload");
      mRawFieldPayload.name("RawFieldPayload");
      mAnychar.name("Anychar");
      mChar.name("Char");
      mSafechar.name("Safechar");
    }

    boost::spirit::qi::rule<SourceIterator, DestinationData()> mFieldColumnRule;
    boost::spirit::qi::rule<SourceIterator, std::string()> mProtectedField;
    boost::spirit::qi::rule<SourceIterator, std::string()> mUnprotectedField;
    boost::spirit::qi::rule<SourceIterator, std::string()> mFieldPayload;
    boost::spirit::qi::rule<SourceIterator, std::string()> mRawFieldPayload;
    boost::spirit::qi::rule<SourceIterator, char()> mAnychar;
    boost::spirit::qi::rule<SourceIterator, char()> mChar;
    boost::spirit::qi::rule<SourceIterator, char()> mSafechar;
  };

}}}} // namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{

#endif // #ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_FIELD_COLUMN_RULE_H
