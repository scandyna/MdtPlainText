/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "catch2/catch.hpp"
#include "Mdt/PlainText/BasicFileInfo_unix.h"
#include <QTemporaryFile>
#include <QTemporaryDir>
#include <QString>
#include <QByteArray>


bool isDirectory(const QString & path)
{
  return Mdt::PlainText::isDirectory( path.toLocal8Bit().toStdString() );
}

TEST_CASE("isDirectory")
{
  SECTION("file")
  {
    QTemporaryFile file;
    REQUIRE( file.open() );

    REQUIRE( !isDirectory( file.fileName() ) );
  }

  SECTION("directory")
  {
    QTemporaryDir dir;
    REQUIRE( dir.isValid() );

    REQUIRE( isDirectory( dir.path() ) );
  }
}
