/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_OPEN_FSTREAM_H
#define MDT_PLAIN_TEXT_OPEN_FSTREAM_H

#include "FileOpenError.h"
#include "FileWriteOpenMode.h"
#include "mdt_plaintext_export.h"
#include <fstream>
#include <string>

namespace Mdt{ namespace PlainText{

  /*! \internal Open \a stream
   *
   * The main goal of this helper function is to fail
   * if \a path refers to a directory
   *
   * \pre \a stream must not allready be open
   * \pre \a path must not be empty
   * \exception FileOpenError
   *
   * \sa https://stackoverflow.com/questions/9591036/ifstream-open-doesnt-set-error-bits-when-argument-is-a-directory
   */
  MDT_PLAINTEXT_EXPORT
  void openIfstream(std::ifstream & stream, const std::string & path);

  /*! \internal Open \a stream
   *
   * \pre \a stream must not allready be open
   * \pre \a path must not be empty
   * \exception FileOpenError
   */
  MDT_PLAINTEXT_EXPORT
  void openOfstream(std::ofstream & stream, const std::string & path, FileWriteOpenMode mode);

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_OPEN_FSTREAM_H
