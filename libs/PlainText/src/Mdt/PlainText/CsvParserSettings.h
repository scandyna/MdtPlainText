/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_CSV_PARSER_SETTINGS_H
#define MDT_PLAIN_TEXT_CSV_PARSER_SETTINGS_H

#include "CsvParserSettingsValidity.h"
#include "mdt_plaintext_export.h"

namespace Mdt{ namespace PlainText{

  /*! \brief CSV parser settings
   *
   * \note Some part of this API documentation
   *       refers to CSV-1203 standard.
   *       CSV-1203 is a open standard available here: http://mastpoint.com/csv-1203
   */
  class MDT_PLAINTEXT_EXPORT CsvParserSettings
  {
   public:

    /*! \brief Construct default settings
     */
    constexpr CsvParserSettings() noexcept = default;

    /*! \brief Copy construct settings from \a other
     */
    constexpr CsvParserSettings(const CsvParserSettings & other) noexcept = default;

    /*! \brief Copy assign \a other to this settings
     */
    constexpr CsvParserSettings & operator=(const CsvParserSettings & other) noexcept = default;

    /*! \brief Move construct settings from \a other
     */
    constexpr CsvParserSettings(CsvParserSettings && other) noexcept = default;

    /*! \brief Move assign \a other to this settings
     */
    constexpr CsvParserSettings & operator=(CsvParserSettings && other) noexcept = default;

    /*! \brief Set field (or column) separator
     *
     * \sa fieldSeparator()
     */
    constexpr void setFieldSeparator(char separator) noexcept
    {
      mFieldSeparator = separator;
    }

    /*! \brief Get field (or column) separator
     *
     * As suggested by CSV-1203 standard, rule 4.3,
     *  the default field separator is comma ","
     *
     * \sa setFieldSeparator()
     */
    constexpr char fieldSeparator() const noexcept
    {
      return mFieldSeparator;
    }

    /*! \brief Set field payload protection
     */
    constexpr void setFieldProtection(char protection) noexcept
    {
      mFieldProtection = protection;
    }

    /*! \brief Get field payload protection
     *
     * Field payload protection is explained
     *  in CSV-1203 standard, §9.
     *
     * The default is the double quote '"' .
     *
     * The ability to choose another protection
     *  is a non standard extention.
     */
    constexpr char fieldProtection() const noexcept
    {
      return mFieldProtection;
    }

    /*! \brief Set if Excel protection marker will be parsed
     *
     * \sa parseExp()
     */
    constexpr void setParseExp(bool parse) noexcept
    {
      mParseExp = parse;
    }

    /*! \brief Check if Excel protection marker will be parsed
     *
     * The Excel protection marker (EXP) is explained
     *  in CSV-1203 standard, §10.
     *
     * When parseExp is true,
     *  when a field begins with a ~ (=EXP),
     *  it will not be stored in resulting data.
     *
     * The ability to not parse EXP
     *  is a non standard extention.
     *
     * \sa setParseExp()
     */
    constexpr bool parseExp() const noexcept
    {
      return mParseExp;
    }

    /*! \brief Validate this settings
     *
     * CSV parser settings are valid if the field separator and field protection are different.
     * Also, if parseExp is true, none of the separator must be the ~ (=EXP).
     */
    constexpr CsvParserSettingsValidity validate() const noexcept
    {
      if(mFieldSeparator == mFieldProtection){
        return CsvParserSettingsValidity::FieldSeparatorAndProtectionAreSame;
      }
      if(mParseExp){
        if(mFieldSeparator == '~'){
          return CsvParserSettingsValidity::FieldSeparatorIsEXP;
        }
        if(mFieldProtection == '~'){
          return CsvParserSettingsValidity::FieldProtectionIsEXP;
        }
      }

      return CsvParserSettingsValidity::Valid;
    }

    /*! \brief Check if this settings are valid
     *
     * \sa validate()
     */
    constexpr bool isValid() const noexcept
    {
      return validate() == CsvParserSettingsValidity::Valid;
    }

   private:

    char mFieldSeparator = ',';
    char mFieldProtection = '"';
    bool mParseExp = true;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_CSV_PARSER_SETTINGS_H
