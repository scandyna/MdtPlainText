/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_QI_PROTECTED_FIELD_H
#define MDT_PLAIN_TEXT_GRAMMAR_CSV_QI_PROTECTED_FIELD_H

#include "Char.h"
#include "Mdt/PlainText/CsvParserSettings.h"
#include <boost/spirit/include/qi.hpp>
#include <cstdint>
#include <cassert>

namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{ namespace Qi{


  /*! \brief CSV protected field rule
   *
   * \note Some part of this API documentation refers to following standards:
   *       \li CSV-1203 available here: https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw
   *       \li RFC 4180 available here: https://tools.ietf.org/html/rfc4180
   */
  template <typename SourceIterator, typename DestinationString>
  struct ProtectedField : boost::spirit::qi::grammar<SourceIterator, DestinationString()>
  {
    /*! \brief Constructor
     *
     * \pre \a settings must be valid
     */
    ProtectedField(const CsvParserSettings & settings) noexcept
     : ProtectedField::base_type(mProtectedField, "ProtectedField"),
       mChar(settings)
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

      if(parseExp){
        mProtectedField = lit(fieldQuote) >> -lit('~') >> mFieldPayload >> lit(fieldQuote);
      }else{
        mProtectedField = lit(fieldQuote) >> mFieldPayload >> lit(fieldQuote);
      }
      mFieldPayload = *mAnychar;
      // Character collections
      mAnychar = mChar | char_(fieldSep) | (char_(fieldQuote) >> lit(fieldQuote)) | space; // space matches space, CR, LF and other See std::isspace()

      BOOST_SPIRIT_DEBUG_NODE(mProtectedField);
      BOOST_SPIRIT_DEBUG_NODE(mFieldPayload);
      BOOST_SPIRIT_DEBUG_NODE(mAnychar);
    }

   private:

    void nameRules()
    {
      mFieldPayload.name("FieldPayload");
      mAnychar.name("Anychar");
    }

    boost::spirit::qi::rule<SourceIterator, DestinationString()> mProtectedField;
    boost::spirit::qi::rule<SourceIterator, DestinationString()> mFieldPayload;
    boost::spirit::qi::rule<SourceIterator, uint32_t()> mAnychar;
    Char<SourceIterator, uint32_t> mChar;
  };

}}}}} // namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{ namespace Qi{

#endif // #ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_QI_PROTECTED_FIELD_H
