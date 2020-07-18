/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "BasicFileInfo_unix.h"
#include <stdexcept>
#include <cassert>
#include <cerrno>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace Mdt{ namespace PlainText{

bool isDirectory(const std::string & path)
{
  assert( !path.empty() );

  struct stat sb;

  if( stat(path.c_str(), &sb) == -1 ){
    throw std::runtime_error( std::strerror(errno) );
  }

  return S_ISDIR(sb.st_mode);
}

}} // namespace Mdt{ namespace PlainText{
