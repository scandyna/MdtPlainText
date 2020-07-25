/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "OpenFstream.h"
#if defined(MDT_OS_UNIX)
 #include "BasicFileInfo_unix.h"
#endif // #if defined(MDT_OS_UNIX)
#include <cassert>

namespace Mdt{ namespace PlainText{

void openIfstream(std::ifstream & stream, const std::string & path)
{
  assert( !stream.is_open() );
  assert( !path.empty() );

  stream.open(path);
  if( stream.bad() || stream.fail() ){
    stream.close();
    const std::string what = "open file '" + path + "' failed";
    throw FileOpenError(what);
  }

  /*
   * On some systems, like Unix,
   * std::ifstream succeeds when open a directory.
   *
   * See also: See https://stackoverflow.com/questions/9591036/ifstream-open-doesnt-set-error-bits-when-argument-is-a-directory
   *
   * On Linux (Ubuntu 18.04) GCC, using peek() works to report a error
   * On Linux Clang, this did not work
   */
#if defined(MDT_OS_UNIX)
  if( isDirectory(path) ){
    stream.close();
    const std::string what = "path '" + path + "' refers to a directory";
    throw FileOpenError(what);
  }
#endif // #if defined(MDT_OS_UNIX)
}

void openOfstream(std::ofstream & stream, const std::string & path, FileWriteOpenMode mode)
{
  assert( !stream.is_open() );
  assert( !path.empty() );

  std::ios_base::openmode openMode;
  switch(mode){
    case FileWriteOpenMode::Append:
      openMode = std::ios_base::out | std::ios_base::binary | std::ios_base::app;
      break;
    case FileWriteOpenMode::Truncate:
      openMode = std::ios_base::out | std::ios_base::binary | std::ios_base::trunc;
      break;
  }

  stream.open(path, openMode);
  if( stream.bad() || stream.fail() ){
    stream.close();
    const std::string what = "open file '" + path + "' failed";
    throw FileOpenError(what);
  }
}

}} // namespace Mdt{ namespace PlainText{
