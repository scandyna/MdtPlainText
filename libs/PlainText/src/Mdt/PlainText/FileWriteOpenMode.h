/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_FILE_WRITE_OPEN_MODE_H
#define MDT_PLAIN_TEXT_FILE_WRITE_OPEN_MODE_H

// #include "mdt_plaintext_export.h"

namespace Mdt{ namespace PlainText{

  /*! \brief File write open mode
   */
  enum class FileWriteOpenMode
  {
    Append,   /*!< Write data to the end of the file */
    Truncate  /*!< The file is truncated, all earlier contents are lost */
  };

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_FILE_WRITE_OPEN_MODE_H
