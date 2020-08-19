/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_KARMA_FIELD_COLUMN_H
#define MDT_PLAIN_TEXT_GRAMMAR_CSV_KARMA_FIELD_COLUMN_H

#include "ProtectedField.h"
#include "UnprotectedField.h"
#include "Mdt/PlainText/CsvGeneratorSettings.h"
#include <boost/spirit/include/karma.hpp>
#include <cstdint>
#include <cassert>

namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{ namespace Karma{

  /*! \brief CSV FieldColumn rule
   *
   * As described in CSV-1203, §9, if a field payload contains at least a field separator,
   * a double-quote or a end of line, it will be protected, otherwise not.
   *
   * \note Some part of this API documentation refers to following standards:
   *       \li CSV-1203 available here: https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw
   *       \li RFC 4180 available here: https://tools.ietf.org/html/rfc4180
   */
  template <typename DestinationIterator, typename SourceString>
  struct FieldColumn : boost::spirit::karma::grammar<DestinationIterator, SourceString()>
  {
    /*! \brief Constructor
     *
     * \pre \a settings must be valid
     */
    FieldColumn(const CsvGeneratorSettings & settings) noexcept
     : FieldColumn::base_type(mFieldColumn, "FieldColumn"),
       mUnprotectedField(settings),
       mProtectedField(settings)
    {
      assert( settings.isValid() );

      mFieldColumn = mUnprotectedField | mProtectedField;

      BOOST_SPIRIT_DEBUG_NODE(mFieldColumn);
    }

   private:

    boost::spirit::karma::rule<DestinationIterator, SourceString()> mFieldColumn;
    UnprotectedField<DestinationIterator, SourceString> mUnprotectedField;
    ProtectedField<DestinationIterator, SourceString> mProtectedField;
  };

}}}}} // namespace Mdt{ namespace PlainText{ namespace Grammar{ namespace Csv{ namespace Karma{

#endif // #ifndef MDT_PLAIN_TEXT_GRAMMAR_CSV_KARMA_FIELD_COLUMN_H
