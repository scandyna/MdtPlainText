/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_CSV_FILE_WRITE_ERROR_H
#define MDT_PLAIN_TEXT_CSV_FILE_WRITE_ERROR_H

#include "mdt_plaintext_export.h"
#include <stdexcept>
#include <string>

namespace Mdt{ namespace PlainText{

  /*! \brief Exception thrown on CSV file write error
   */
  class MDT_PLAINTEXT_EXPORT CsvFileWriteError : public std::runtime_error
  {
   public:

    /*! \brief Constructor
     */
    explicit CsvFileWriteError(const std::string & what)
     : runtime_error(what)
    {
    }
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_CSV_FILE_WRITE_ERROR_H
