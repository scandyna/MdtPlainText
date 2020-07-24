/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_CSV_GENERATOR_SETTINGS_VALIDITY_H
#define MDT_PLAIN_TEXT_CSV_GENERATOR_SETTINGS_VALIDITY_H

namespace Mdt{ namespace PlainText{

  /*! \brief Validity of CsvGeneratorSettings
   */
  enum class CsvGeneratorSettingsValidity
  {
    Valid,                              /*!< Settings are valid */
    FieldSeparatorAndProtectionAreSame, /*!< Field separator and field protection are the same */
    FieldSeparatorIsEXP,                /*!< Field separator is the ~ (=EXP) */
    FieldProtectionIsEXP                /*!< Field protection is the ~ (=EXP) */
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_CSV_GENERATOR_SETTINGS_VALIDITY_H
