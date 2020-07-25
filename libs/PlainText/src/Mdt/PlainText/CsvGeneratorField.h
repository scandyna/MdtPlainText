/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_CSV_GENERATOR_FIELD_H
#define MDT_PLAIN_TEXT_CSV_GENERATOR_FIELD_H

#include "mdt_plaintext_export.h"
#include <string>

namespace Mdt{ namespace PlainText{

  /*! \brief CSV generator field
   *
   * CsvGeneratorField is a simple wrapper around a std::string
   * and adding a state to know if a field must be protected or not.
   *
   * Example to create a record:
   * \code
   * using Record = std::vector<CsvGeneratorField>;
   *
   * Record record1{{"A"},{"B"},{"C"}};
   *
   * Record record2{
   *   {"A", CsvGeneratorField::DoProtect},
   *   {"2", CsvGeneratorField::DoNotProtect},
   *   "C"
   * };
   *
   * Record record3{{"A"},{"2"}};
   * record3[0].doProtect();
   * record3[1].doNotProtect();
   * \endcode
   *
   * Example of a helper function to create a record:
   * \code
   * std::vector<CsvGeneratorField> csvRecordFromStringList(const MyData & data)
   * {
   *   return std::vector<CsvGeneratorField> record{
   *     {convertToString( data.number() ), CsvGeneratorField::DoNotProtect},
   *     {data.text(), CsvGeneratorField::DoNotProtect}
   *   };
   * }
   * \endcode
   *
   * Example to use a record:
   * \code
   * using Record = std::vector<CsvGeneratorField>;
   *
   * Record record{...};
   * for(const auto & field : record){
   *   if( field.haveToProtect() ){
   *     writeQuotedField( field.value() );
   *   }else{
   *     writeUnquotedField( field.value() );
   *   }
   * }
   * \endcode
   */
  class MDT_PLAINTEXT_EXPORT CsvGeneratorField
  {
   public:

    /*! \brief Field protection
     */
    enum Protection
    {
      DoProtect,    /*!< Field have to be protected */
      DoNotProtect  /*!< Field have not to be protected */
    };

    CsvGeneratorField() = delete;

    /*! \brief Construct a field
     */
    CsvGeneratorField(const std::string & str, Protection protection = DoProtect)
     : mValue(str),
       mProtection(protection)
    {
    }

    /*! \brief Copy construct a field from \a other
     */
    CsvGeneratorField(const CsvGeneratorField & other) = default;

    /*! \brief Copy assign \a other to this field
     */
    CsvGeneratorField & operator=(const CsvGeneratorField & other) = default;

    /*! \brief Move construct a field from \a other
     */
    CsvGeneratorField(CsvGeneratorField && other) noexcept = default;

    /*! \brief Move assign \a other to this field
     */
    CsvGeneratorField & operator=(CsvGeneratorField && other) noexcept = default;

    /*! \brief Flag this field to be protected
     */
    void doProtect()
    {
      mProtection = DoProtect;
    }

    /*! \brief Flag this field to not be protected
     */
    void doNotProtect()
    {
      mProtection = DoNotProtect;
    }

    /*! \brief Check if this field has to be protected
     */
    bool haveToProtect() const noexcept
    {
      return mProtection == DoProtect;
    }

    /*! \brief Get the value of this field
     */
    const std::string & value() const noexcept
    {
      return mValue;
    }

   private:

    std::string mValue;
    Protection mProtection;
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_CSV_GENERATOR_FIELD_H
