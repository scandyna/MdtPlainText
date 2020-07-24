/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_GENERATOR_SETTINGS_H
#define MDT_PLAIN_TEXT_GENERATOR_SETTINGS_H

#include "EndOfLine.h"
#include "CsvGeneratorSettingsValidity.h"
#include "mdt_plaintext_export.h"
#include <cassert>

namespace Mdt{ namespace PlainText{

  /*! \brief CSV generator settings
   *
   * \note Some part of this API documentation
   *       refers to CSV-1203 standard.
   *       CSV-1203 is a open standard available here: https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw
   */
  class MDT_PLAINTEXT_EXPORT CsvGeneratorSettings
  {
   public:

    /*! \brief Construct default settings
     */
    constexpr CsvGeneratorSettings() noexcept = default;

    /*! \brief Copy construct settings from \a other
     */
    constexpr CsvGeneratorSettings(const CsvGeneratorSettings & other) noexcept = default;

    /*! \brief Copy assign \a other to this settings
     */
    constexpr CsvGeneratorSettings & operator=(const CsvGeneratorSettings & other) noexcept = default;

    /*! \brief Move construct settings from \a other
     */
    constexpr CsvGeneratorSettings(CsvGeneratorSettings && other) noexcept = default;

    /*! \brief Move assign \a other to this settings
     */
    constexpr CsvGeneratorSettings & operator=(CsvGeneratorSettings && other) noexcept = default;

    /*! \brief Set field (or column) separator
     *
     * \pre \a separator must not be a end-of-line
     * \sa isEndOfLine()
     * \sa fieldSeparator()
     */
    constexpr void setFieldSeparator(char separator) noexcept
    {
      assert( !isEndOfLine(separator) );

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
     *
     * \pre \a protection must not be a end-of-line
     * \sa isEndOfLine()
     * \sa fieldProtection()
     */
    constexpr void setFieldProtection(char protection) noexcept
    {
      assert( !isEndOfLine(protection) );

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
     *
     * \sa setFieldProtection()
     */
    constexpr char fieldProtection() const noexcept
    {
      return mFieldProtection;
    }

    /*! \brief Set if Excel protection marker should be added
     *
     * \sa addExp()
     */
    constexpr void setAddExp(bool add) noexcept
    {
      mAddExp = add;
    }

    /*! \brief Check if Excel protection marker should be added
     *
     * The Excel protection marker (EXP) is explained
     *  in CSV-1203 standard, §10.
     *
     * When addExp is true,
     *  a ~ (=EXP) will be added at the beginning of the fiel payload.
     *
     * By default, no EXP will be added.
     *
     * \sa setAddExp()
     */
    constexpr bool addExp() const noexcept
    {
      return mAddExp;
    }

    /*! \brief Set the end-of-line
     *
     * \sa endOfLine()
     */
    constexpr void setEndOfLine(EndOfLine eol) noexcept
    {
      mEndOfLine = eol;
    }

    /*! \brief Get the end-of-line
     *
     * The default end-of-line is EndOfLine::Native
     *
     * \sa setEndOfLine()
     */
    constexpr EndOfLine endOfLine() const noexcept
    {
      return mEndOfLine;
    }

    /*! \brief Validate this settings
     *
     * CSV generator settings are valid if the field separator and field protection are different.
     * Also, if addExp is true, none of the separator must be the ~ (=EXP).
     */
    constexpr CsvGeneratorSettingsValidity validate() const noexcept
    {
      if(mFieldSeparator == mFieldProtection){
        return CsvGeneratorSettingsValidity::FieldSeparatorAndProtectionAreSame;
      }
      if(mAddExp){
        if(mFieldSeparator == '~'){
          return CsvGeneratorSettingsValidity::FieldSeparatorIsEXP;
        }
        if(mFieldProtection == '~'){
          return CsvGeneratorSettingsValidity::FieldProtectionIsEXP;
        }
      }

      return CsvGeneratorSettingsValidity::Valid;
    }

    /*! \brief Check if this settings are valid
     *
     * \sa validate()
     */
    constexpr bool isValid() const noexcept
    {
      return validate() == CsvGeneratorSettingsValidity::Valid;
    }

    /*! \brief Check if \a c is a end-of-line
     */
    static
    constexpr bool isEndOfLine(char c) noexcept
    {
      if(c == '\n'){
        return true;
      }
      if(c == '\r'){
        return true;
      }
      return false;
    }

   private:

    char mFieldSeparator = ',';
    char mFieldProtection = '"';
    bool mAddExp = false;
    EndOfLine mEndOfLine = EndOfLine::Native;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_GENERATOR_SETTINGS_H
