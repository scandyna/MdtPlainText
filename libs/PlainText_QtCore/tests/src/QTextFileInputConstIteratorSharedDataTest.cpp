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
#include "QTextFileInputConstIteratorSharedDataTestCommon.h"


TEST_CASE("Check UTF-8 support")
{
  REQUIRE( QTextCodec::codecForName("UTF-8") != nullptr );
}

TEST_CASE("atEnd")
{
  QTemporaryFile file;
  REQUIRE( file.open() );

  int rawBufferCapacity = GENERATE(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 128, 1024);

  SECTION("Empty file")
  {
    QTextFileInputConstIteratorSharedData sd(&file, "UTF-8", rawBufferCapacity);
    REQUIRE( sd.atEnd() );
  }

  SECTION("A")
  {
    REQUIRE( writeTextFile(file, QLatin1String("A")) );
    file.close();

    REQUIRE( openTextFileReadOnly(file) );
    QTextFileInputConstIteratorSharedData sd(&file, "UTF-8", rawBufferCapacity);
    REQUIRE( !sd.atEnd() );
  }

  SECTION("ABCD")
  {
    REQUIRE( writeTextFile(file, QLatin1String("ABCD")) );
    file.close();

    REQUIRE( openTextFileReadOnly(file) );
    QTextFileInputConstIteratorSharedData sd(&file, "UTF-8", rawBufferCapacity);
    REQUIRE( !sd.atEnd() );
  }
}

TEST_CASE("get")
{
  QTemporaryFile file;
  REQUIRE( file.open() );

  SECTION("A")
  {
    REQUIRE( writeTextFile(file, QLatin1String("A")) );
    file.close();

    REQUIRE( openTextFileReadOnly(file) );
    QTextFileInputConstIteratorSharedData sd(&file, "UTF-8");
    REQUIRE( !sd.atEnd() );
    REQUIRE( sd.get() == QLatin1Char('A') );
  }

  SECTION("ö")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("ö")) );
    file.close();

    REQUIRE( openTextFileReadOnly(file) );
    QTextFileInputConstIteratorSharedData sd(&file, "UTF-8");
    REQUIRE( !sd.atEnd() );
    REQUIRE( sd.get().unicode() == 0x00F6 );
  }

  SECTION("ĵ")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("ĵ")) );
    file.close();

    REQUIRE( openTextFileReadOnly(file) );
    QTextFileInputConstIteratorSharedData sd(&file, "UTF-8");
    REQUIRE( !sd.atEnd() );
    REQUIRE( sd.get().unicode() == 0x0135 );
  }
}

TEST_CASE("advance_get")
{
  QTemporaryFile file;
  REQUIRE( file.open() );

  int rawBufferCapacity = GENERATE(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 128, 1024);

  SECTION("A")
  {
    REQUIRE( writeTextFile(file, QLatin1String("A")) );
    file.close();

    REQUIRE( openTextFileReadOnly(file) );
    QTextFileInputConstIteratorSharedData sd(&file, "UTF-8", rawBufferCapacity);
    REQUIRE( !sd.atEnd() );
    REQUIRE( sd.get() == QLatin1Char('A') );
    sd.advance();
    REQUIRE( sd.atEnd() );
  }

  SECTION("AB")
  {
    REQUIRE( writeTextFile(file, QLatin1String("AB")) );
    file.close();

    REQUIRE( openTextFileReadOnly(file) );
    QTextFileInputConstIteratorSharedData sd(&file, "UTF-8", rawBufferCapacity);
    REQUIRE( !sd.atEnd() );
    REQUIRE( sd.get() == QLatin1Char('A') );
    sd.advance();
    REQUIRE( !sd.atEnd() );
    REQUIRE( sd.get() == QLatin1Char('B') );
    sd.advance();
    REQUIRE( sd.atEnd() );
  }

  SECTION("ABC")
  {
    REQUIRE( writeTextFile(file, QLatin1String("ABC")) );
    file.close();

    REQUIRE( openTextFileReadOnly(file) );
    QTextFileInputConstIteratorSharedData sd(&file, "UTF-8", rawBufferCapacity);
    REQUIRE( !sd.atEnd() );
    REQUIRE( sd.get() == QLatin1Char('A') );
    sd.advance();
    REQUIRE( !sd.atEnd() );
    REQUIRE( sd.get() == QLatin1Char('B') );
    sd.advance();
    REQUIRE( !sd.atEnd() );
    REQUIRE( sd.get() == QLatin1Char('C') );
    sd.advance();
    REQUIRE( sd.atEnd() );
  }

  SECTION("AöB")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("AöB")) );
    file.close();

    REQUIRE( openTextFileReadOnly(file) );
    QTextFileInputConstIteratorSharedData sd(&file, "UTF-8", rawBufferCapacity);
    REQUIRE( !sd.atEnd() );
    REQUIRE( sd.get() == QLatin1Char('A') );
    sd.advance();
    REQUIRE( !sd.atEnd() );
    REQUIRE( sd.get().unicode() == 0x00F6 );
    sd.advance();
    REQUIRE( !sd.atEnd() );
    REQUIRE( sd.get() == QLatin1Char('B') );
    sd.advance();
    REQUIRE( sd.atEnd() );
  }
}
