/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_BASIC_FILE_INFO_UNIX_H
#define MDT_PLAIN_TEXT_BASIC_FILE_INFO_UNIX_H

#include "mdt_plaintext_export.h"
#include <string>

namespace Mdt{ namespace PlainText{

  /*! \internal Check if \a path refers to a directory
   *
   * \pre \a path must not be empty
   * \exception std::runtime_error
   */
  MDT_PLAINTEXT_EXPORT
  bool isDirectory(const std::string & path);

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_BASIC_FILE_INFO_UNIX_H
