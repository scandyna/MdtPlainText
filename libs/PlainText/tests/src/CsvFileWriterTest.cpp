/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "CsvFileWriterTestCommon.h"

TEST_CASE("filePath")
{
  CsvFileWriter writer;

  SECTION("default")
  {
    REQUIRE( writer.filePath().empty() );
  }

  SECTION("set and get")
  {
    writer.setFilePath("test.csv");
    REQUIRE( writer.filePath() == "test.csv" );
  }
}

TEST_CASE("csvSettings")
{
  CsvFileWriter writer;

  SECTION("default")
  {
    REQUIRE( writer.csvSettings().fieldSeparator() == ',' );
  }

  SECTION("set and get")
  {
    CsvGeneratorSettings settings;
    settings.setFieldSeparator(';');
    writer.setCsvSettings(settings);
    REQUIRE( writer.csvSettings().fieldSeparator() == ';' );
  }
}

TEST_CASE("openMode")
{
  CsvFileWriter writer;

  SECTION("default")
  {
    REQUIRE( writer.openMode() == FileWriteOpenMode::Append );
  }

  SECTION("set and get")
  {
    writer.setOpenMode(FileWriteOpenMode::Truncate);
    REQUIRE( writer.openMode() == FileWriteOpenMode::Truncate );
  }
}

TEST_CASE("open_close")
{
  QTemporaryDir dir;
  REQUIRE( dir.isValid() );

  CsvFileWriter writer;
  REQUIRE( !writer.isOpen() );

  const QString filePath = filePathFromDirAndFileName(dir, "test.csv");
  setFilePathToWriter(filePath, writer);
  REQUIRE( !writer.isOpen() );

  writer.open();
  REQUIRE( writer.isOpen() );

  writer.close();
  REQUIRE( !writer.isOpen() );
}

TEST_CASE("open")
{
  QTemporaryDir dir;
  REQUIRE( dir.isValid() );

  CsvFileWriter writer;

  SECTION("Append")
  {
    writer.setOpenMode(FileWriteOpenMode::Append);

    SECTION("New file")
    {
      const QString filePath = filePathFromDirAndFileName(dir, "new.csv");
      setFilePathToWriter(filePath, writer);
      REQUIRE( !fileExists(filePath) );

      writer.open();
      writer.close();
      REQUIRE( fileExists(filePath) );
    }

    SECTION("Existing file")
    {
      const QString filePath = filePathFromDirAndFileName(dir, "existing.csv");
      const QString originalFileContent = QLatin1String("ABC");
      REQUIRE( writeTextFile(filePath, originalFileContent) );
      REQUIRE( fileExists(filePath) );

      setFilePathToWriter(filePath, writer);
      writer.open();
      writer.close();
      REQUIRE( fileExists(filePath) );
      REQUIRE( readTextFile(filePath) == originalFileContent );
    }
  }

  SECTION("Trucate")
  {
    writer.setOpenMode(FileWriteOpenMode::Truncate);

    SECTION("New file")
    {
      const QString filePath = filePathFromDirAndFileName(dir, "new.csv");
      setFilePathToWriter(filePath, writer);
      REQUIRE( !fileExists(filePath) );

      writer.open();
      writer.close();
      REQUIRE( fileExists(filePath) );
    }

    SECTION("Existing file")
    {
      const QString filePath = filePathFromDirAndFileName(dir, "existing.csv");
      REQUIRE( writeTextFile(filePath, QLatin1String("ABC")) );
      REQUIRE( fileExists(filePath) );

      setFilePathToWriter(filePath, writer);
      writer.open();
      writer.close();
      REQUIRE( fileExists(filePath) );
      REQUIRE( readTextFile(filePath).isEmpty() );
    }
  }
}
