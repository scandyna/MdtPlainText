/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_KARMA_UNPROTECTED_FIELD_H
#define MDT_PLAIN_TEXT_GRAMMAR_CSV_KARMA_UNPROTECTED_FIELD_H

#include "Mdt/PlainText/CsvGeneratorSettings.h"
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/qi.hpp>
#include <iterator>
#include <cassert>

namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{ namespace Karma{

  /*! \internal
   */
  struct ValidateStringForUnprotectedField
  {
    constexpr ValidateStringForUnprotectedField(const CsvGeneratorSettings & settings) noexcept
     : mCsvSettings(settings)
    {
    }

    template<typename String>
    bool operator()(const String & str) const
    {
      using iterator = typename String::const_iterator;

      const int stringLen = std::distance(str.begin(), str.end());

      if(stringLen < 1){
        return true;
      }

      using boost::spirit::unicode::char_;
      using boost::spirit::lit;
      using boost::spirit::repeat;

      const char fieldSep = mCsvSettings.fieldSeparator();
      const char fieldQuote = mCsvSettings.fieldProtection();

      boost::spirit::qi::rule<iterator> validString;
      boost::spirit::qi::rule<iterator> safeChar;
      boost::spirit::qi::rule<iterator> Char;

      if(stringLen == 1){
        // validString = safeChar; throws a runtime exception
        validString = safeChar >> -safeChar;
      }else if(stringLen == 2){
        validString = safeChar >> safeChar;
      }else{
        assert(stringLen > 2);
        const int max = stringLen-2;
        validString = safeChar >> repeat(0,max)[Char] >> safeChar;
      }

      const std::string exclude = std::string("\n\t\r ") + fieldSep + fieldQuote;
      safeChar = ~char_(exclude);

      Char = safeChar | lit(' ');

      BOOST_SPIRIT_DEBUG_NODE(validString);
      BOOST_SPIRIT_DEBUG_NODE(safeChar);
      BOOST_SPIRIT_DEBUG_NODE(Char);

      return boost::spirit::qi::parse(str.begin(), str.end(), validString);
    }

    const CsvGeneratorSettings & mCsvSettings;
  };

  /*! \brief CSV UnprotectedField rule
   *
   * If the attribute string provided statisfies the unprotected filed rules it will be returned as is,
   * otherwise it will fail.
   *
   * For example, if the string contains any "unsafe" char, like a separator,
   * a field protection or a end of line, this rule will fail.
   *
   * As stated in CSV-1203, §3.4, leading and trailing spaces are not accepted
   * (if they exist, they must be protected).
   *
   * \note Some part of this API documentation refers to following standards:
   *       \li CSV-1203 available here: https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw
   *       \li RFC 4180 available here: https://tools.ietf.org/html/rfc4180
   */
  template <typename DestinationIterator, typename SourceString>
  struct UnprotectedField : boost::spirit::karma::grammar<DestinationIterator, SourceString()>
  {
    using CharType = typename SourceString::value_type;

    /*! \brief Constructor
     *
     * \pre \a settings must be valid
     */
    UnprotectedField(const CsvGeneratorSettings & settings) noexcept
     : UnprotectedField::base_type(mUnprotectedField, "UnprotectedField")
    {
      assert( settings.isValid() );

      using boost::spirit::karma::unicode::char_;

      using boost::spirit::karma::eps;
      using boost::spirit::karma::_val;
      using boost::spirit::lit;

      const bool addExp = settings.addExp();

      boost::phoenix::function<ValidateStringForUnprotectedField> validateString(settings);

      if(addExp){
        mUnprotectedField = eps( validateString(_val) ) << lit('~') << *char_;
      }else{
        mUnprotectedField = eps( validateString(_val) ) << *char_;
      }

      BOOST_SPIRIT_DEBUG_NODE(mUnprotectedField);
    }

   private:

    boost::spirit::karma::rule<DestinationIterator, SourceString()> mUnprotectedField;
  };

}}}}} // namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{ namespace Karma{

#endif // #ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_KARMA_UNPROTECTED_FIELD_H
