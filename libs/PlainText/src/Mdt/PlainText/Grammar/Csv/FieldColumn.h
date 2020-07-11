/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_FIELD_COLUMN_H
#define MDT_PLAIN_TEXT_GRAMMAR_CSV_FIELD_COLUMN_H

#include "ProtectedField.h"
#include "UnprotectedField.h"
#include "Mdt/PlainText/CsvParserSettings.h"
#include <boost/spirit/include/qi.hpp>
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
    /*! \brief Constructor
     *
     * \pre \a settings must be valid
     */
    FieldColumn(const CsvParserSettings & settings) noexcept
     : FieldColumn::base_type(mFieldColumn),
       mProtectedField(settings),
       mUnprotectedField(settings)
    {
      assert( settings.isValid() );

      nameRules();

      mFieldColumn = mProtectedField | mUnprotectedField;

      BOOST_SPIRIT_DEBUG_NODE(mFieldColumn);
    }

   private:

    void nameRules()
    {
      mFieldColumn.name("FieldColumn");
    }

    boost::spirit::qi::rule<SourceIterator, DestinationString()> mFieldColumn;
    ProtectedField<SourceIterator, DestinationString> mProtectedField;
    UnprotectedField<SourceIterator, DestinationString> mUnprotectedField;
  };

}}}} // namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{

#endif // #ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_FIELD_COLUMN_H
