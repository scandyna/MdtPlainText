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
#include "BoostSpiritQTextFileInputConstIteratorTestCommon.h"

/*
 * Tests for LegacyIterator requirements
 */

static_assert( std::is_copy_constructible<BoostSpiritQTextFileInputConstIterator>::value , "" );
static_assert( std::is_copy_assignable<BoostSpiritQTextFileInputConstIterator>::value , "" );
static_assert( std::is_destructible<BoostSpiritQTextFileInputConstIterator>::value , "" );

TEST_CASE("copy_construct")
{
  QTemporaryFile file;
  REQUIRE( file.open() );
  REQUIRE( writeTextFile(file, QLatin1String("ABC")) );
  file.close();

  REQUIRE( openTextFileReadOnly(file) );
  BoostSpiritQTextFileInputConstIterator a(&file, "UTF-8");

  BoostSpiritQTextFileInputConstIterator b(a);
  REQUIRE( *b == QLatin1Char('A') );
}

TEST_CASE("assign")
{
  QTemporaryFile file;
  REQUIRE( file.open() );
  REQUIRE( writeTextFile(file, QLatin1String("ABC")) );
  file.close();

  REQUIRE( openTextFileReadOnly(file) );
  BoostSpiritQTextFileInputConstIterator a(&file, "UTF-8");

  BoostSpiritQTextFileInputConstIterator b;

  b = a;
  REQUIRE( *b == QLatin1Char('A') );
}

TEST_CASE("pre-increment")
{
  QTemporaryFile file;
  REQUIRE( file.open() );
  REQUIRE( writeTextFile(file, QLatin1String("ABC")) );
  file.close();

  REQUIRE( openTextFileReadOnly(file) );
  BoostSpiritQTextFileInputConstIterator it(&file, "UTF-8");

  ++it;
  REQUIRE( *it == QLatin1Char('B') );
}

/*
 * Tests for LegacyInputIterator requirements
 */

TEST_CASE("post-increment")
{
  QTemporaryFile file;
  REQUIRE( file.open() );
  REQUIRE( writeTextFile(file, QLatin1String("ABC")) );
  file.close();

  REQUIRE( openTextFileReadOnly(file) );
  BoostSpiritQTextFileInputConstIterator it(&file, "UTF-8");

  it++;
  REQUIRE( *it == QLatin1Char('B') );
}

TEST_CASE("comparison")
{
  QTemporaryFile file;
  REQUIRE( file.open() );
  REQUIRE( writeTextFile(file, QLatin1String("ABC")) );
  file.close();

  REQUIRE( openTextFileReadOnly(file) );
  BoostSpiritQTextFileInputConstIterator a(&file, "UTF-8");
  auto b = a;

  REQUIRE( a == b );
  REQUIRE( !(a != b) );
}

/*
 * Tests with some STL functions
 */

TEST_CASE("std_copy")
{
  QTemporaryFile file;
  REQUIRE( file.open() );
  QString destination;
  BoostSpiritQTextFileInputConstIterator last;

  SECTION("abcd")
  {
    const QString source = QLatin1String("abcd");
    REQUIRE( writeTextFile(file, source) );
    file.close();

    REQUIRE( openTextFileReadOnly(file) );
    BoostSpiritQTextFileInputConstIterator first(&file, "UTF-8");
    std::copy( first, last, std::back_inserter(destination) );
    REQUIRE( destination == source );
  }

  SECTION("éöàäèü$£")
  {
    const QString source = QStringLiteral(u"\u00E9\u00F6\u00E0\u00E4\u00E8\u00FC$\u00A3");
    REQUIRE( writeTextFile(file, source) );
    file.close();

    REQUIRE( openTextFileReadOnly(file) );
    BoostSpiritQTextFileInputConstIterator first(&file, "UTF-8");
    std::copy( first, last, std::back_inserter(destination) );
    REQUIRE( destination == source );
  }
}

/*
 * Tests with some Sprit parsers
 */

TEST_CASE("qi_parser_int_")
{
  using boost::spirit::int_;

  QTemporaryFile file;
  REQUIRE( file.open() );
  int result;

  SECTION("24")
  {
    REQUIRE( writeTextFile(file, QLatin1String("24")) );
    file.close();

    REQUIRE( openTextFileReadOnly(file) );
    REQUIRE( parse(file, int_, result) );
    REQUIRE( result == 24 );
  }
}

TEST_CASE("qi_parser_unicode_char_")
{
  using boost::spirit::unicode::char_;

  QTemporaryFile file;
  REQUIRE( file.open() );
  QString result;

  SECTION("ABC")
  {
    REQUIRE( writeTextFile(file, QLatin1String("ABC")) );
    file.close();

    REQUIRE( openTextFileReadOnly(file) );
    REQUIRE( parse(file, *char_, result) );
    REQUIRE( result == QLatin1String("ABC") );
  }

  SECTION("éöàäèü$£")
  {
    const QString source = QStringLiteral(u"\u00E9\u00F6\u00E0\u00E4\u00E8\u00FC$\u00A3");
    REQUIRE( writeTextFile(file, source) );
    file.close();

    REQUIRE( openTextFileReadOnly(file) );
    REQUIRE( parse(file, *char_, result) );
    REQUIRE( result == source );
  }

  SECTION("a𐐅ö")
  {
    const QString source = QString::fromUtf8("a\xF0\x90\x90\x85\xC3\xB6");
    REQUIRE( writeTextFile(file, source) );
    file.close();

    REQUIRE( openTextFileReadOnly(file) );
    REQUIRE( parse(file, *char_, result) );
    REQUIRE( result == source );
  }

  SECTION("char_(A)")
  {
    REQUIRE( writeTextFile(file, QLatin1String("ABC")) );
    file.close();

    QChar result;
    REQUIRE( openTextFileReadOnly(file) );
    REQUIRE( parse(file, char_('A'), result) );
    REQUIRE( result == QLatin1Char('A') );
  }

  SECTION("char_(ö)")
  {
    REQUIRE( writeTextFile(file, QStringLiteral(u"\u00F6")) );
    file.close();

    QChar result;
    REQUIRE( openTextFileReadOnly(file) );
    REQUIRE( parse(file, char_(U'\U000000F6'), result) );
    REQUIRE( result == QChar(0xF6) );
  }
}
