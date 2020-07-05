/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_CSV_PARSER_TEMPLATE_H
#define MDT_PLAIN_TEXT_CSV_PARSER_TEMPLATE_H

#include "CsvParserSettings.h"
#include "CsvParseError.h"
#include "Mdt/PlainText/Grammar/Csv/RecordRule.h"
#include <boost/spirit/include/qi.hpp>
#include <cassert>

namespace Mdt{ namespace PlainText{

  /*! \brief CSV parser template
   *
   * This class implements the parser logic,
   *  and can act on different containers
   *  that have STL compatible iterators.
   *
   * \tparam SourceIterator Type of iterator that will act on the source.
   *    Must be at least a forward iterator.
   *
   * \note Including directly this header in a project can slow down compilation time
   * \sa CsvStringParser
   * \sa CsvFileReader
   */
  template <typename SourceIterator>
  class CsvParserTemplate
  {
   public:

    /*! \brief Constructor
     */
    CsvParserTemplate() noexcept = default;

    CsvParserTemplate(const CsvParserTemplate &)  noexcept = delete;
    CsvParserTemplate & operator=(const CsvParserTemplate &)  noexcept = delete;
    CsvParserTemplate(CsvParserTemplate &&)  noexcept = delete;
    CsvParserTemplate & operator=(CsvParserTemplate &&)  noexcept = delete;

    /*! \brief Set CSV settings
     *
     * \pre \a settings must be valid
     */
    void setCsvSettings(const CsvParserSettings & settings) noexcept
    {
      assert( settings.isValid() );

      mCsvSettings = settings;
    }

    /*! \brief Get CSV settings
     */
    const CsvParserSettings & csvSettings() const noexcept
    {
      return mCsvSettings;
    }

    /*! \brief Read a line from the CSV data
     *
     * \exception CsvParseError
     */
    template<typename Record>
    Record readLine(const SourceIterator & first, const SourceIterator & last) const
    {
      Record record;
      Grammar::Csv::RecordRule<SourceIterator, Record> rule(mCsvSettings);

      const bool ok = boost::spirit::qi::parse(first, last, rule, record);
      if(!ok){
        throw CsvParseError("CSV parsing failed");
      }

      return record;
    }

   private:

    CsvParserSettings mCsvSettings;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_CSV_PARSER_TEMPLATE_H
