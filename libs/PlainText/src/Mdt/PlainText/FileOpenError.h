/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_FILE_OPEN_ERROR_H
#define MDT_PLAIN_TEXT_FILE_OPEN_ERROR_H

#include "mdt_plaintext_export.h"
#include <stdexcept>
#include <string>

namespace Mdt{ namespace PlainText{

  /*! \brief Exception thrown when a file connot be open
   */
  class MDT_PLAINTEXT_EXPORT FileOpenError : public std::runtime_error
  {
   public:

    /*! \brief Constructor
     */
    explicit FileOpenError(const std::string & what)
     : runtime_error(what)
    {
    }
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_FILE_OPEN_ERROR_H
