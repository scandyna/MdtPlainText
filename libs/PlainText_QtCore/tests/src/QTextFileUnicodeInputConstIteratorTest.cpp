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
#include "QTextFileUnicodeInputConstIteratorTestCommon.h"
#include <type_traits>
#include <algorithm>

/*
 * Private implementation tests
 */

using Mdt::PlainText::Impl::QTextFileUnicodeInputConstIteratorImpl;

QTextFileUnicodeInputConstIteratorImpl iteratorImplFromFile(QFile & file)
{
  return QTextFileUnicodeInputConstIteratorImpl(&file, "UTF-8");
}


TEST_CASE("Impl_construct")
{
  QTemporaryFile file;
  REQUIRE( file.open() );

  SECTION("empty")
  {
    file.close();
    REQUIRE( openTextFileReadOnly(file) );
    const auto it = iteratorImplFromFile(file);
    REQUIRE( it.currentCodeUint.isNull() );
    REQUIRE( it.codePoint == 0 );
  }

  SECTION("A")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("A")) );
    REQUIRE( openTextFileReadOnly(file) );
    auto it = iteratorImplFromFile(file);
    REQUIRE( it.currentCodeUint == QLatin1Char('A') );
  }
}

TEST_CASE("Impl_atEnd")
{
  QTemporaryFile file;
  REQUIRE( file.open() );

  SECTION("empty")
  {
    file.close();
    REQUIRE( openTextFileReadOnly(file) );
    const auto it = iteratorImplFromFile(file);
    REQUIRE( it.atEnd() );
  }

  SECTION("A")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("A")) );
    REQUIRE( openTextFileReadOnly(file) );
    auto it = iteratorImplFromFile(file);
    REQUIRE( !it.atEnd() );

    ++it.mIterator;
    REQUIRE( it.atEnd() );
  }
}

TEST_CASE("Impl_isDereferencable")
{
  QTemporaryFile file;
  REQUIRE( file.open() );

  SECTION("Default constructed iterator is not dereferencable")
  {
    QTextFileUnicodeInputConstIteratorImpl it;
    REQUIRE( !it.isDereferencable() );
  }

  SECTION("empty")
  {
    file.close();
    REQUIRE( openTextFileReadOnly(file) );
    const auto it = iteratorImplFromFile(file);
    REQUIRE( !it.isDereferencable() );
  }

  SECTION("Single char A is dereferencable, then increment, then its not")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("A")) );
    REQUIRE( openTextFileReadOnly(file) );
    auto it = iteratorImplFromFile(file);
    REQUIRE( it.isDereferencable() );

    ++it.mIterator;
    REQUIRE( !it.isDereferencable() );
  }
}

TEST_CASE("Impl_increment")
{
  QTemporaryFile file;
  REQUIRE( file.open() );

  SECTION("A")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("A")) );
    REQUIRE( openTextFileReadOnly(file) );
    auto it = iteratorImplFromFile(file);
    REQUIRE( !it.atEnd() );
    REQUIRE( it.isDereferencable() );
    REQUIRE( it.currentCodeUint == QLatin1Char('A') );

    it.increment();
    REQUIRE( it.atEnd() );
    REQUIRE( !it.isDereferencable() );
  }

  SECTION("AB")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("AB")) );
    REQUIRE( openTextFileReadOnly(file) );
    auto it = iteratorImplFromFile(file);
    REQUIRE( !it.atEnd() );
    REQUIRE( it.isDereferencable() );
    REQUIRE( it.currentCodeUint == QLatin1Char('A') );

    it.increment();
    REQUIRE( !it.atEnd() );
    REQUIRE( it.isDereferencable() );
    REQUIRE( it.currentCodeUint == QLatin1Char('B') );

    it.increment();
    REQUIRE( it.atEnd() );
    REQUIRE( !it.isDereferencable() );
  }

  SECTION("Single code unit char: ĵ (U+0135)")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("ĵ")) );
    REQUIRE( openTextFileReadOnly(file) );
    auto it = iteratorImplFromFile(file);
    REQUIRE( !it.atEnd() );
    REQUIRE( it.isDereferencable() );
    REQUIRE( it.currentCodeUint.unicode() == u'\u0135' );

    it.increment();
    REQUIRE( it.atEnd() );
    REQUIRE( !it.isDereferencable() );
  }

  SECTION("Code point requiring 2 UTF-16 units: 𐐅")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("𐐅")) );
    REQUIRE( openTextFileReadOnly(file) );
    auto it = iteratorImplFromFile(file);

    /*
     * Code point | 𐐅 |
     * Surrogate  |H|L|
     *             ^
     */
    REQUIRE( !it.atEnd() );
    REQUIRE( it.isDereferencable() );

    /*
     * Code point | 𐐅 |
     * Surrogate  |H|L|
     *                 ^
     */
    it.increment();
    REQUIRE( it.atEnd() );
    REQUIRE( !it.isDereferencable() );
  }

  SECTION("A𐐅")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("A𐐅")) );
    REQUIRE( openTextFileReadOnly(file) );
    auto it = iteratorImplFromFile(file);

    /*
     * Code point |A| 𐐅 |
     * Surrogate  | |H|L|
     *             ^
     */
    REQUIRE( !it.atEnd() );
    REQUIRE( it.isDereferencable() );
    REQUIRE( it.currentCodeUint == QLatin1Char('A') );

    /*
     * Code point |A| 𐐅 |
     * Surrogate  | |H|L|
     *               ^
     */
    it.increment();
    REQUIRE( !it.atEnd() );
    REQUIRE( it.isDereferencable() );

    /*
     * Code point |A| 𐐅 |
     * Surrogate  | |H|L|
     *                   ^
     */
    it.increment();
    REQUIRE( it.atEnd() );
    REQUIRE( !it.isDereferencable() );
  }

  SECTION("𐐅A")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("𐐅A")) );
    REQUIRE( openTextFileReadOnly(file) );
    auto it = iteratorImplFromFile(file);

    /*
     * Code point | 𐐅 |A|
     * Surrogate  |H|L| |
     *             ^
     */
    REQUIRE( !it.atEnd() );
    REQUIRE( it.isDereferencable() );

    /*
     * Code point | 𐐅 |A|
     * Surrogate  |H|L| |
     *                 ^
     */
    it.increment();
    REQUIRE( !it.atEnd() );
    REQUIRE( it.isDereferencable() );
    REQUIRE( it.currentCodeUint == QLatin1Char('A') );

    /*
     * Code point | 𐐅 |A|
     * Surrogate  |H|L| |
     *                   ^
     */
    it.increment();
    REQUIRE( it.atEnd() );
    REQUIRE( !it.isDereferencable() );
  }

  SECTION("𐐅𝛀 (U+10405 U+1D6C0)")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("𐐅𝛀")) );
    REQUIRE( openTextFileReadOnly(file) );
    auto it = iteratorImplFromFile(file);

    /*
     * Code point | 𐐅 | 𝛀 |
     * Surrogate  |H|L|H|L|
     *             ^
     */
    REQUIRE( !it.atEnd() );
    REQUIRE( it.isDereferencable() );

    /*
     * Code point | 𐐅 | 𝛀 |
     * Surrogate  |H|L|H|L|
     *                 ^
     */
    it.increment();
    REQUIRE( !it.atEnd() );
    REQUIRE( it.isDereferencable() );

    /*
     * Code point | 𐐅 | 𝛀 |
     * Surrogate  |H|L|H|L|
     *                     ^
     */
    it.increment();
    REQUIRE( it.atEnd() );
    REQUIRE( !it.isDereferencable() );
  }
}

TEST_CASE("Impl_extractCodePoint")
{
  QTemporaryFile file;
  REQUIRE( file.open() );

  SECTION("A")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("A")) );
    REQUIRE( openTextFileReadOnly(file) );
    auto it = iteratorImplFromFile(file);

    it.extractCodePoint();
    REQUIRE( it.codePoint == U'A' );
  }

  SECTION("AB")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("AB")) );
    REQUIRE( openTextFileReadOnly(file) );
    auto it = iteratorImplFromFile(file);

    it.extractCodePoint();
    REQUIRE( it.codePoint == U'A' );

    it.increment();
    it.extractCodePoint();
    REQUIRE( it.codePoint == U'B' );
  }

  SECTION("ĵ")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("ĵ")) );
    REQUIRE( openTextFileReadOnly(file) );
    auto it = iteratorImplFromFile(file);

    it.extractCodePoint();
    REQUIRE( it.codePoint == U'\U00000135' );
  }

  SECTION("𐐅")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("𐐅")) );
    REQUIRE( openTextFileReadOnly(file) );
    auto it = iteratorImplFromFile(file);

    it.extractCodePoint();
    REQUIRE( it.codePoint == U'\U00010405' );
  }

  SECTION("A𐐅")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("A𐐅")) );
    REQUIRE( openTextFileReadOnly(file) );
    auto it = iteratorImplFromFile(file);

    it.extractCodePoint();
    REQUIRE( it.codePoint == U'A' );

    it.increment();
    it.extractCodePoint();
    REQUIRE( it.codePoint == U'\U00010405' );
  }

  SECTION("𐐅A")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("𐐅A")) );
    REQUIRE( openTextFileReadOnly(file) );
    auto it = iteratorImplFromFile(file);

    it.extractCodePoint();
    REQUIRE( it.codePoint == U'\U00010405' );

    it.increment();
    it.extractCodePoint();
    REQUIRE( it.codePoint == U'A' );
  }

  SECTION("𐐅𝛀 (U+10405 U+1D6C0)")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("𐐅𝛀")) );
    REQUIRE( openTextFileReadOnly(file) );
    auto it = iteratorImplFromFile(file);

    it.extractCodePoint();
    REQUIRE( it.codePoint == U'\U00010405' );

    it.increment();
    it.extractCodePoint();
    REQUIRE( it.codePoint == U'\U0001D6C0' );
  }
}

/*
 * Iterator interface tests
 */

TEST_CASE("construct")
{
  QTemporaryFile file;
  REQUIRE( file.open() );

  SECTION("empty file")
  {
    file.close();
    REQUIRE( openTextFileReadOnly(file) );
    QTextFileUnicodeInputConstIterator it(&file, "UTF-8");
  }

  SECTION("A")
  {
    REQUIRE( writeTextFile(file, QLatin1String("ABC")) );
    REQUIRE( openTextFileReadOnly(file) );
    QTextFileUnicodeInputConstIterator it(&file, "UTF-8");
    REQUIRE( *it == U'A' );
  }
}

/*
 * Tests for LegacyIterator requirements
 */

static_assert( std::is_copy_constructible<QTextFileUnicodeInputConstIterator>::value , "" );
static_assert( std::is_copy_assignable<QTextFileUnicodeInputConstIterator>::value , "" );
static_assert( std::is_destructible<QTextFileUnicodeInputConstIterator>::value , "" );

TEST_CASE("copy_construct")
{
  QTemporaryFile file;
  REQUIRE( file.open() );
  REQUIRE( writeTextFile(file, QLatin1String("ABC")) );
  file.close();

  REQUIRE( openTextFileReadOnly(file) );
  QTextFileUnicodeInputConstIterator a(&file, "UTF-8");

  QTextFileUnicodeInputConstIterator b(a);
  REQUIRE( *b == QLatin1Char('A') );
}

TEST_CASE("assign")
{
  QTemporaryFile file;
  REQUIRE( file.open() );
  REQUIRE( writeTextFile(file, QLatin1String("ABC")) );
  file.close();

  REQUIRE( openTextFileReadOnly(file) );
  QTextFileUnicodeInputConstIterator a(&file, "UTF-8");

  QTextFileUnicodeInputConstIterator b;

  b = a;
  REQUIRE( *b == QLatin1Char('A') );
}

TEST_CASE("pre-increment")
{
  QTemporaryFile file;
  REQUIRE( file.open() );

  SECTION("AB")
  {
    REQUIRE( writeTextFile(file, QLatin1String("AB")) );

    REQUIRE( openTextFileReadOnly(file) );
    QTextFileUnicodeInputConstIterator it(&file, "UTF-8");
    REQUIRE( *it == U'A' );

    ++it;
    REQUIRE( *it == U'B' );
  }

  SECTION("A𐐅")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("A𐐅")) );

    REQUIRE( openTextFileReadOnly(file) );
    QTextFileUnicodeInputConstIterator it(&file, "UTF-8");
    REQUIRE( *it == U'A' );

    ++it;
    REQUIRE( *it == U'\U00010405' );
  }

  SECTION("𐐅A")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("𐐅A")) );

    REQUIRE( openTextFileReadOnly(file) );
    QTextFileUnicodeInputConstIterator it(&file, "UTF-8");
    REQUIRE( *it == U'\U00010405' );

    ++it;
    REQUIRE( *it == U'A' );
  }
}

/*
 * Tests for LegacyInputIterator requirements
 */

TEST_CASE("post-increment")
{
  QTemporaryFile file;
  REQUIRE( file.open() );

  SECTION("AB")
  {
    REQUIRE( writeTextFile(file, QLatin1String("AB")) );

    REQUIRE( openTextFileReadOnly(file) );
    QTextFileUnicodeInputConstIterator it(&file, "UTF-8");
    REQUIRE( *it == U'A' );

    it++;
    REQUIRE( *it == U'B' );
  }

  SECTION("A𐐅")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("A𐐅")) );

    REQUIRE( openTextFileReadOnly(file) );
    QTextFileUnicodeInputConstIterator it(&file, "UTF-8");
    REQUIRE( *it == U'A' );

    it++;
    REQUIRE( *it == U'\U00010405' );
  }

  SECTION("𐐅A")
  {
    REQUIRE( writeTextFile(file, QString::fromUtf8("𐐅A")) );

    REQUIRE( openTextFileReadOnly(file) );
    QTextFileUnicodeInputConstIterator it(&file, "UTF-8");
    REQUIRE( *it == U'\U00010405' );

    it++;
    REQUIRE( *it == U'A' );
  }
}

TEST_CASE("comparison")
{
  QTemporaryFile file;
  REQUIRE( file.open() );
  REQUIRE( writeTextFile(file, QLatin1String("ABC")) );
  file.close();

  REQUIRE( openTextFileReadOnly(file) );
  QTextFileUnicodeInputConstIterator a(&file, "UTF-8");
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
  QTextFileUnicodeInputConstIterator last;

  SECTION("abcd")
  {
    const QString source = QLatin1String("abcd");
    REQUIRE( writeTextFile(file, source) );
    file.close();

    REQUIRE( openTextFileReadOnly(file) );
    QTextFileUnicodeInputConstIterator first(&file, "UTF-8");
    std::copy( first, last, std::back_inserter(destination) );
    REQUIRE( destination == source );
  }

  SECTION("éöàäèü$£")
  {
    const QString source = QStringLiteral(u"\u00E9\u00F6\u00E0\u00E4\u00E8\u00FC$\u00A3");
    REQUIRE( writeTextFile(file, source) );
    file.close();

    REQUIRE( openTextFileReadOnly(file) );
    QTextFileUnicodeInputConstIterator first(&file, "UTF-8");
    std::copy( first, last, std::back_inserter(destination) );
    REQUIRE( destination == source );
  }
}
