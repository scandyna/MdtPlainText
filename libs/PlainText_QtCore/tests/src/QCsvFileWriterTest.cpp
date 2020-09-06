/****************************************************************************
 **
 ** MdtPlainText - A C++ library to read and write simple plain text
 ** using the boost Spirit library.
 **
 ** Copyright (C) 2020-2020 Philippe Steinmann.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with this program.  If not, see <https://www.gnu.org/licenses/>.
 **
 ****************************************************************************/
#include "QCsvFileWriterTestCommon.h"

TEST_CASE("filePath")
{
  QCsvFileWriter writer;

  SECTION("default")
  {
    REQUIRE( writer.filePath().isEmpty() );
  }

  SECTION("set and get")
  {
    writer.setFilePath( QLatin1String("test.csv") );
    REQUIRE( writer.filePath() == QLatin1String("test.csv") );
  }
}

TEST_CASE("fileEncoding")
{
  QCsvFileWriter writer;
  REQUIRE( writer.fileEncoding() == "UTF-8" );

  writer.setFileEncoding("ISO 8859-1");
  REQUIRE( writer.fileEncoding() == "ISO 8859-1" );
}

TEST_CASE("csvSettings")
{
  QCsvFileWriter writer;

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
  QCsvFileWriter writer;

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

  QCsvFileWriter writer;
  REQUIRE( !writer.isOpen() );

  const QString filePath = filePathFromDirAndFileName(dir, "test.csv");
  writer.setFilePath(filePath);
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

  QCsvFileWriter writer;

  SECTION("Append")
  {
    writer.setOpenMode(FileWriteOpenMode::Append);

    SECTION("New file")
    {
      const QString filePath = filePathFromDirAndFileName(dir, "new.csv");
      writer.setFilePath(filePath);
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

      writer.setFilePath(filePath);
      writer.open();
      writer.close();
      REQUIRE( fileExists(filePath) );
      REQUIRE( readTextFile(filePath) == originalFileContent );
    }
  }

  SECTION("Truncate")
  {
    writer.setOpenMode(FileWriteOpenMode::Truncate);

    SECTION("New file")
    {
      const QString filePath = filePathFromDirAndFileName(dir, "new.csv");
      writer.setFilePath(filePath);
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

      writer.setFilePath(filePath);
      writer.open();
      writer.close();
      REQUIRE( fileExists(filePath) );
      REQUIRE( readTextFile(filePath).isEmpty() );
    }
  }
}

TEST_CASE("writeLine")
{
  QTemporaryDir dir;
  REQUIRE( dir.isValid() );

  CsvGeneratorSettings csvSettings;
  csvSettings.setEndOfLine(EndOfLine::Lf);

  QCsvFileWriter writer;
  writer.setCsvSettings(csvSettings);
  const QString filePath = filePathFromDirAndFileName(dir, "file.csv");
  writer.setFilePath(filePath);
  writer.open();

  QStringList record;
  QString fileData;

  SECTION("A")
  {
    record = qStringListFromStdStringList({"A"});
    writer.writeLine(record);
    writer.close();
    fileData = readTextFile(filePath);
    REQUIRE( fileData == QLatin1String("A\n") );
  }

  SECTION("AB|cdéàäö")
  {
    record = qStringListFromStdStringList({"AB","cdéàäö"});
    writer.writeLine(record);
    writer.close();
    fileData = readTextFile(filePath);
    REQUIRE( fileData == QString::fromUtf8("AB,cdéàäö\n") );
  }

  SECTION("a b𝛀|c, de𐐅")
  {
    record = qStringListFromStdStringList({"a b𝛀","c, de𐐅"});
    writer.writeLine(record);
    writer.close();
    fileData = readTextFile(filePath);
    REQUIRE( fileData == QString::fromUtf8("a b𝛀,\"c, de𐐅\"\n") );
  }

  SECTION("ab𐐅c|DE\\n12𝛀|3456")
  {
    record = qStringListFromStdStringList({"ab𐐅c","DE"});
    writer.writeLine(record);
    record = qStringListFromStdStringList({"12𝛀","3456"});
    writer.writeLine(record);
    writer.close();
    fileData = readTextFile(filePath);
    REQUIRE( fileData == QString::fromUtf8("ab𐐅c,DE\n12𝛀,3456\n") );
  }
}

TEST_CASE("writeTable")
{
  QTemporaryDir dir;
  REQUIRE( dir.isValid() );

  CsvGeneratorSettings csvSettings;
  csvSettings.setEndOfLine(EndOfLine::Lf);

  QCsvFileWriter writer;
  writer.setCsvSettings(csvSettings);
  const QString filePath = filePathFromDirAndFileName(dir, "file.csv");
  writer.setFilePath(filePath);
  writer.open();

  std::vector<QStringList> table;
  QString fileData;

  SECTION("A")
  {
    table = qStringTableFromStdStringTable({{"A"}});
    writer.writeTable(table);
    writer.close();
    fileData = readTextFile(filePath);
    REQUIRE( fileData == QString::fromUtf8("A\n") );
  }

  SECTION("A𐐅 C|D,é\\n79|34𝛀 56")
  {
    table = qStringTableFromStdStringTable({{"A𐐅 C","D,é"},{"79","34𝛀 56"}});
    writer.writeTable(table);
    writer.close();
    fileData = readTextFile(filePath);
    REQUIRE( fileData == QString::fromUtf8("A𐐅 C,\"D,é\"\n79,34𝛀 56\n") );
  }
}
