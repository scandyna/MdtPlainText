/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "CsvFileReaderTestCommon.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>

TEST_CASE("sandbox")
{
  struct stat sb;

  if( stat("/tmp", &sb) == -1 ){
    std::cerr << "stat() failed" << std::endl;
    return;
  }
  std::cout << "is dir: " << S_ISDIR(sb.st_mode) << std::endl;
}

TEST_CASE("open")
{
  CsvFileReader reader;

  SECTION("File not exists")
  {
    reader.setFilePath("/some/non/exising/file.csv");

    REQUIRE_THROWS_AS( reader.open(), FileOpenError );
    REQUIRE( !reader.isOpen() );
  }

  SECTION("Path refers to a directory")
  {
    QTemporaryDir dir;
    REQUIRE( dir.isValid() );

    setDirectoryPathToReader(dir, reader);

    REQUIRE_THROWS_AS( reader.open(), FileOpenError );
    REQUIRE( !reader.isOpen() );
  }
}
