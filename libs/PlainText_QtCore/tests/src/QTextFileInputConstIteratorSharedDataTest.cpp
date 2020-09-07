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
#include <memory>

int readFromFile(QBuffer & file, std::vector<char> & buffer)
{
  return Mdt::PlainText::Impl::readFromFile(file, QLatin1String("TestBuffer"), buffer);
}

bool readFromFileAndDecode(QBuffer & file, std::vector<char> & rawDataBuffer, QString & unicodeBuffer)
{
  QTextCodec *codec = QTextCodec::codecForName("UTF-8");
  assert( codec != nullptr );
  std::unique_ptr<QTextDecoder> decoder( codec->makeDecoder() );
  assert( decoder.get() != nullptr );

  return Mdt::PlainText::Impl::readFromFileAndDecode(file, QLatin1String("TestBuffer"), *decoder, rawDataBuffer, unicodeBuffer);
}

int rawBufferSize(const std::vector<char> & buffer)
{
  return buffer.size();
}

TEST_CASE("Check UTF-8 support")
{
  REQUIRE( QTextCodec::codecForName("UTF-8") != nullptr );
}

TEST_CASE("readFromFile")
{
  QBuffer file;

  SECTION("Raw buffer capacity: 1")
  {
    std::vector<char> rawBuffer;
    rawBuffer.reserve(1);

    SECTION("A")
    {
      file.setData("A");
      REQUIRE( openQBufferReadOnly(file) );

      REQUIRE( readFromFile(file, rawBuffer) == 1 );
      REQUIRE( file.atEnd() );
      REQUIRE( rawBufferSize(rawBuffer) == 1 );
      REQUIRE( rawBuffer[0] == 'A' );
    }

    SECTION("AB")
    {
      file.setData("AB");
      REQUIRE( openQBufferReadOnly(file) );

      REQUIRE( readFromFile(file, rawBuffer) == 1 );
      REQUIRE( !file.atEnd() );
      REQUIRE( rawBufferSize(rawBuffer) == 1 );
      REQUIRE( rawBuffer[0] == 'A' );
      rawBuffer.clear();

      REQUIRE( readFromFile(file, rawBuffer) == 1 );
      REQUIRE( file.atEnd() );
      REQUIRE( rawBufferSize(rawBuffer) == 1 );
      REQUIRE( rawBuffer[0] == 'B' );
    }

    SECTION("ABC")
    {
      file.setData("ABC");
      REQUIRE( openQBufferReadOnly(file) );

      REQUIRE( readFromFile(file, rawBuffer) == 1 );
      REQUIRE( !file.atEnd() );
      REQUIRE( rawBufferSize(rawBuffer) == 1 );
      REQUIRE( rawBuffer[0] == 'A' );
      rawBuffer.clear();

      REQUIRE( readFromFile(file, rawBuffer) == 1 );
      REQUIRE( !file.atEnd() );
      REQUIRE( rawBufferSize(rawBuffer) == 1 );
      REQUIRE( rawBuffer[0] == 'B' );
      rawBuffer.clear();

      REQUIRE( readFromFile(file, rawBuffer) == 1 );
      REQUIRE( file.atEnd() );
      REQUIRE( rawBufferSize(rawBuffer) == 1 );
      REQUIRE( rawBuffer[0] == 'C' );
    }
  }

  SECTION("Raw buffer capacity: 2")
  {
    std::vector<char> rawBuffer;
    rawBuffer.reserve(2);

    SECTION("A")
    {
      file.setData("A");
      REQUIRE( openQBufferReadOnly(file) );

      REQUIRE( readFromFile(file, rawBuffer) == 1 );
      REQUIRE( file.atEnd() );
      REQUIRE( rawBufferSize(rawBuffer) == 1 );
      REQUIRE( rawBuffer[0] == 'A' );
    }

    SECTION("AB")
    {
      file.setData("AB");
      REQUIRE( openQBufferReadOnly(file) );

      REQUIRE( readFromFile(file, rawBuffer) == 2 );
      REQUIRE( file.atEnd() );
      REQUIRE( rawBufferSize(rawBuffer) == 2 );
      REQUIRE( rawBuffer[0] == 'A' );
      REQUIRE( rawBuffer[1] == 'B' );
    }

    SECTION("ABC")
    {
      file.setData("ABC");
      REQUIRE( openQBufferReadOnly(file) );

      REQUIRE( readFromFile(file, rawBuffer) == 2 );
      REQUIRE( !file.atEnd() );
      REQUIRE( rawBufferSize(rawBuffer) == 2 );
      REQUIRE( rawBuffer[0] == 'A' );
      REQUIRE( rawBuffer[1] == 'B' );
      rawBuffer.clear();

      REQUIRE( readFromFile(file, rawBuffer) == 1 );
      REQUIRE( file.atEnd() );
      REQUIRE( rawBufferSize(rawBuffer) == 1 );
      REQUIRE( rawBuffer[0] == 'C' );
    }
  }
}

/*
 * Extract this function to be able to test it reliably
 * Because we don't know how many bytes QFile (which uses system read calls)
 * returns, sporadic bugs have bee detected, not reproductible of my machine.
 * See for example: https://gitlab.com/scandyna/mdtplaintext/-/jobs/638021363
 *
 * Here we try to emulate some scenarios
 */
TEST_CASE("readFromFileAndDecode")
{
  QString unicodeBuffer;
  QBuffer file;

  /*
   * rawBuffer capacity: 1
   *
   * Initial:
   * | rawBuffer | unicodeBuffer |
   * -----------------------------
   * | []        | []            |
   *
   * Read 1 from file:
   * | rawBuffer | unicodeBuffer |
   * -----------------------------
   * | [A]       | []            |
   *
   * Decode 1 byte:
   * | rawBuffer | unicodeBuffer |
   * -----------------------------
   * | []        | [A]           |
   */
  SECTION("A")
  {
    std::vector<char> rawBuffer;
    rawBuffer.reserve(1);

    file.setData("A");
    REQUIRE( openQBufferReadOnly(file) );

    REQUIRE( readFromFileAndDecode(file, rawBuffer, unicodeBuffer) );
    REQUIRE( file.atEnd() );
    REQUIRE( rawBuffer.empty() );
    REQUIRE( unicodeBuffer == QLatin1String("A") );
  }

  SECTION("AB")
  {
    std::vector<char> rawBuffer;
    rawBuffer.reserve(1);

    file.setData("AB");
    REQUIRE( openQBufferReadOnly(file) );

    REQUIRE( readFromFileAndDecode(file, rawBuffer, unicodeBuffer) );
    REQUIRE( !file.atEnd() );
    REQUIRE( rawBuffer.empty() );
    REQUIRE( unicodeBuffer == QLatin1String("A") );

    unicodeBuffer.clear();
    REQUIRE( readFromFileAndDecode(file, rawBuffer, unicodeBuffer) );
    REQUIRE( file.atEnd() );
    REQUIRE( rawBuffer.empty() );
    REQUIRE( unicodeBuffer == QLatin1String("B") );
  }

  /*
   * rawBuffer capacity: 1
   *
   * Initial:
   * | rawBuffer | unicodeBuffer |
   * -----------------------------
   * | []        | []            |
   *
   * Read 1 from file:
   * | rawBuffer | unicodeBuffer |
   * -----------------------------
   * | [0xC4]    | []            |
   *
   * Decode 1 byte (QTextDecoder holds its state):
   * | rawBuffer | unicodeBuffer |
   * -----------------------------
   * | []        | []            |
   *
   * Read 1 from file:
   * | rawBuffer | unicodeBuffer |
   * -----------------------------
   * | [0xB5]    | []            |
   *
   * Decode 1 byte:
   * | rawBuffer | unicodeBuffer |
   * -----------------------------
   * | []        | [ĵ]           |
   */
  SECTION("ĵ")
  {
    std::vector<char> rawBuffer;
    rawBuffer.reserve(1);

    file.setData("\xC4\xB5");
    REQUIRE( openQBufferReadOnly(file) );

    REQUIRE( readFromFileAndDecode(file, rawBuffer, unicodeBuffer) );
    REQUIRE( file.atEnd() );
    REQUIRE( rawBuffer.empty() );
    REQUIRE( unicodeBuffer == QString::fromUtf8("ĵ") );
  }
}

TEST_CASE("atEnd")
{
  QTemporaryFile file;
  REQUIRE( file.open() );

  int rawBufferCapacity = GENERATE(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 128, 1024);

  SECTION("Empty file")
  {
    QTextFileInputConstIteratorSharedData sd(file, "UTF-8", rawBufferCapacity);
    REQUIRE( sd.atEnd() );
  }

  SECTION("A")
  {
    REQUIRE( writeTextFile(file, QLatin1String("A")) );
    file.close();

    REQUIRE( openTextFileReadOnly(file) );
    QTextFileInputConstIteratorSharedData sd(file, "UTF-8", rawBufferCapacity);
    REQUIRE( !sd.atEnd() );
  }

  SECTION("ABCD")
  {
    REQUIRE( writeTextFile(file, QLatin1String("ABCD")) );
    file.close();

    REQUIRE( openTextFileReadOnly(file) );
    QTextFileInputConstIteratorSharedData sd(file, "UTF-8", rawBufferCapacity);
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
    QTextFileInputConstIteratorSharedData sd(file, "UTF-8");
    REQUIRE( !sd.atEnd() );
    REQUIRE( sd.get() == QLatin1Char('A') );
  }

  SECTION("ö")
  {
    REQUIRE( writeTextFile(file, QStringLiteral(u"\u00F6")) );
    file.close();

    REQUIRE( openTextFileReadOnly(file) );
    QTextFileInputConstIteratorSharedData sd(file, "UTF-8");
    REQUIRE( !sd.atEnd() );
    REQUIRE( sd.get().unicode() == 0x00F6 );
  }

  SECTION("ĵ")
  {
    REQUIRE( writeTextFile(file, QStringLiteral(u"\u0135")) );
    file.close();

    REQUIRE( openTextFileReadOnly(file) );
    QTextFileInputConstIteratorSharedData sd(file, "UTF-8");
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
    QTextFileInputConstIteratorSharedData sd(file, "UTF-8", rawBufferCapacity);
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
    QTextFileInputConstIteratorSharedData sd(file, "UTF-8", rawBufferCapacity);
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
    QTextFileInputConstIteratorSharedData sd(file, "UTF-8", rawBufferCapacity);
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
    REQUIRE( writeTextFile(file, QStringLiteral(u"A\u00F6B")) );
    file.close();

    REQUIRE( openTextFileReadOnly(file) );
    QTextFileInputConstIteratorSharedData sd(file, "UTF-8", rawBufferCapacity);
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
