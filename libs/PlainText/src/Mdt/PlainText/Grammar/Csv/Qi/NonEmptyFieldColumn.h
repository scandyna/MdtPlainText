/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_QI_NON_EMPTY_FIELD_COLUMN_H
#define MDT_PLAIN_TEXT_GRAMMAR_CSV_QI_NON_EMPTY_FIELD_COLUMN_H

#include "ProtectedField.h"
#include "NonEmptyUnprotectedField.h"
#include "Mdt/PlainText/CsvParserSettings.h"
#include <boost/spirit/include/qi.hpp>
#include <cassert>

namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{ namespace Qi{

  /*! \brief CSV non empty field column rule
   *
   * \note Some part of this API documentation refers to following standards:
   *       \li CSV-1203 available here: https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw
   *       \li RFC 4180 available here: https://tools.ietf.org/html/rfc4180
   */
  template <typename SourceIterator, typename DestinationString>
  struct NonEmptyFieldColumn : boost::spirit::qi::grammar<SourceIterator, DestinationString()>
  {
    /*! \brief Constructor
     *
     * \pre \a settings must be valid
     */
    NonEmptyFieldColumn(const CsvParserSettings & settings) noexcept
     : NonEmptyFieldColumn::base_type(mNonEmptyFieldColumn, "NonEmptyFieldColumn"),
       mProtectedField(settings),
       mNonEmptyUnprotectedField(settings)
    {
      assert( settings.isValid() );

      nameRules();

      mNonEmptyFieldColumn = mProtectedField | mNonEmptyUnprotectedField;

      BOOST_SPIRIT_DEBUG_NODE(mNonEmptyFieldColumn);
    }

   private:

    void nameRules()
    {
      mNonEmptyFieldColumn.name("NonEmptyFieldColumn");
    }

    boost::spirit::qi::rule<SourceIterator, DestinationString()> mNonEmptyFieldColumn;
    ProtectedField<SourceIterator, DestinationString> mProtectedField;
    NonEmptyUnprotectedField<SourceIterator, DestinationString> mNonEmptyUnprotectedField;
  };

}}}}} // namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{ namespace Qi{

#endif // #ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_QI_NON_EMPTY_FIELD_COLUMN_H
