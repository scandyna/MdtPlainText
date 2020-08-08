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
#include "catch2/catch.hpp"
#include "Mdt/PlainText/QStringConstIterator.h"
#include <QLatin1String>
#include <type_traits>
#include <iterator>

using Mdt::PlainText::QStringConstIterator;
using Mdt::PlainText::Impl::BoostSpiritQStringConstIteratorData;

/*
 * Private implementation tests
 */

BoostSpiritQStringConstIteratorData iteratorDataFromString(const QString & str)
{
  return BoostSpiritQStringConstIteratorData( str.cbegin(), str.cbegin(), str.cend() );
}

BoostSpiritQStringConstIteratorData iteratorDataFromStringWithPos(const QString & str, QString::const_iterator pos)
{
  BoostSpiritQStringConstIteratorData data;

  data.begin = str.cbegin();
  data.position = pos;
  data.end = str.cend();

  return data;
}

TEST_CASE("Impl_hasNext")
{
  SECTION("empty")
  {
    const QString str;
    const auto data = iteratorDataFromString(str);
    REQUIRE( !data.hasNext() );
  }

  SECTION("A")
  {
    const QString str = QLatin1String("A");
    const auto data = iteratorDataFromString(str);
    REQUIRE( !data.hasNext() );
  }

  SECTION("AB")
  {
    const QString str = QLatin1String("AB");
    const auto data = iteratorDataFromString(str);
    REQUIRE( data.hasNext() );
  }
}

TEST_CASE("Impl_hasPrevious")
{
  SECTION("empty")
  {
    const QString str;
    const auto data = iteratorDataFromString(str);
    REQUIRE( !data.hasPrevious() );
  }

  SECTION("A")
  {
    const QString str = QLatin1String("A");
    const auto data = iteratorDataFromString(str);
    REQUIRE( !data.hasPrevious() );
  }

  SECTION("AB - at beginning")
  {
    const QString str = QLatin1String("AB");
    const auto data = iteratorDataFromString(str);
    REQUIRE( !data.hasPrevious() );
  }

  SECTION("AB - at end")
  {
    const QString str = QLatin1String("AB");
    auto data = iteratorDataFromString(str);
    ++data.position;
    REQUIRE( data.hasPrevious() );
  }
}

TEST_CASE("Impl_atEnd")
{
  SECTION("empty")
  {
    const QString str;
    const auto data = iteratorDataFromString(str);
    REQUIRE( data.atEnd() );
  }

  SECTION("A")
  {
    const QString str = QLatin1String("A");
    auto data = iteratorDataFromString(str);
    REQUIRE( !data.atEnd() );

    ++data.position;
    REQUIRE( data.atEnd() );
  }
}

TEST_CASE("Impl_atBegin")
{
  SECTION("empty")
  {
    const QString str;
    const auto data = iteratorDataFromString(str);
    REQUIRE( data.atBegin() );
  }

  SECTION("A")
  {
    const QString str = QLatin1String("A");
    auto data = iteratorDataFromString(str);
    REQUIRE( data.atBegin() );

    ++data.position;
    REQUIRE( !data.atBegin() );
  }
}

TEST_CASE("Impl_isDereferencable")
{
  SECTION("Default constructed iterator is not dereferencable")
  {
    BoostSpiritQStringConstIteratorData data;
    data.begin = nullptr;
    data.position = nullptr;
    data.end = nullptr;
    REQUIRE( !data.isDereferencable() );
  }

  SECTION("empty")
  {
    const QString str;
    const auto data = iteratorDataFromString(str);
    REQUIRE( !data.isDereferencable() );
  }

  SECTION("Single char A is dereferencable, then increment, then its not")
  {
    const QString str = QLatin1String("A");
    auto data = iteratorDataFromString(str);
    REQUIRE( data.isDereferencable() );

    ++data.position;
    REQUIRE( !data.isDereferencable() );
  }
}

TEST_CASE("Impl_increment")
{
  SECTION("A")
  {
    const QString str = QLatin1String("A");
    auto data = iteratorDataFromString(str);
    REQUIRE( data.position == str.cbegin() );

    data.increment();
    REQUIRE( data.position == str.cend() );
    REQUIRE( data.atEnd() );
  }

  SECTION("AB")
  {
    const QString str = QLatin1String("AB");
    auto data = iteratorDataFromString(str);
    REQUIRE( data.position == str.cbegin() );

    data.increment();
    REQUIRE( data.position == str.cbegin()+1 );

    data.increment();
    REQUIRE( data.position == str.cend() );
  }

  SECTION("Single code unit char: ĵ (U+0135)")
  {
    const QString str = QString::fromUtf8("ĵ");
    auto data = iteratorDataFromString(str);
    REQUIRE( data.position == str.cbegin() );

    data.increment();
    REQUIRE( data.position == str.cend() );
  }

  SECTION("Code point requiring 2 UTF-16 units: 𐐅")
  {
    const QString str = QString::fromUtf8("𐐅");
    auto data = iteratorDataFromString(str);

    /*
     * Code point | 𐐅 |
     * Surrogate  |H|L|
     *             ^
     */
    REQUIRE( data.position == str.cbegin() );

    /*
     * Code point | 𐐅 |
     * Surrogate  |H|L|
     *                 ^
     */
    data.increment();
    REQUIRE( data.position == str.cend() );
  }

  SECTION("A𐐅")
  {
    const QString str = QString::fromUtf8("A𐐅");
    auto data = iteratorDataFromString(str);

    /*
     * Code point |A| 𐐅 |
     * Surrogate  | |H|L|
     *             ^
     */
    REQUIRE( data.position == str.cbegin() );

    /*
     * Code point |A| 𐐅 |
     * Surrogate  | |H|L|
     *               ^
     */
    data.increment();
    REQUIRE( data.position == str.cbegin()+1 );

    /*
     * Code point |A| 𐐅 |
     * Surrogate  | |H|L|
     *                   ^
     */
    data.increment();
    REQUIRE( data.position == str.cend() );
  }

  SECTION("𐐅A")
  {
    const QString str = QString::fromUtf8("𐐅A");
    auto data = iteratorDataFromString(str);

    /*
     * Code point | 𐐅 |A|
     * Surrogate  |H|L| |
     *             ^
     */
    REQUIRE( data.position == str.cbegin() );

    /*
     * Code point | 𐐅 |A|
     * Surrogate  |H|L| |
     *                 ^
     */
    data.increment();
    REQUIRE( data.position == str.cbegin()+2 );

    /*
     * Code point | 𐐅 |A|
     * Surrogate  |H|L| |
     *                   ^
     */
    data.increment();
    REQUIRE( data.position == str.cend() );
  }

  SECTION("𐐅𝛀 (U+10405 U+1D6C0)")
  {
    const QString str = QString::fromUtf8("𐐅𝛀");
    auto data = iteratorDataFromString(str);

    /*
     * Code point | 𐐅 | 𝛀 |
     * Surrogate  |H|L|H|L|
     *             ^
     */
    REQUIRE( data.position == str.cbegin() );

    /*
     * Code point | 𐐅 | 𝛀 |
     * Surrogate  |H|L|H|L|
     *                 ^
     */
    data.increment();
    REQUIRE( data.position == str.cbegin()+2 );

    /*
     * Code point | 𐐅 | 𝛀 |
     * Surrogate  |H|L|H|L|
     *                     ^
     */
    data.increment();
    REQUIRE( data.position == str.cend() );
  }
}

TEST_CASE("Impl_decrement")
{
  SECTION("A")
  {
    const QString str = QLatin1String("A");

    /*
     * Code point |A|
     * Surrogate  | |
     *               ^
     */
    auto data = iteratorDataFromStringWithPos( str, str.cend() );
    REQUIRE( data.position == str.cend() );

    /*
     * Code point |A|
     * Surrogate  | |
     *             ^
     */
    data.decrement();
    REQUIRE( data.position == str.cbegin() );
  }

  SECTION("AB")
  {
    const QString str = QLatin1String("AB");

    /*
     * Code point |A|B|
     * Surrogate  | | |
     *                 ^
     */
    auto data = iteratorDataFromStringWithPos( str, str.cend() );
    REQUIRE( data.position == str.cend() );

    /*
     * Code point |A|B|
     * Surrogate  | | |
     *               ^
     */
    data.decrement();
    REQUIRE( data.position == str.cbegin()+1 );

    /*
     * Code point |A|B|
     * Surrogate  | | |
     *             ^
     */
    data.decrement();
    REQUIRE( data.position == str.cbegin() );
  }

  SECTION("Single code unit char: ĵ (U+0135)")
  {
    const QString str = QString::fromUtf8("ĵ");

    /*
     * Code point |ĵ|
     * Surrogate  | |
     *               ^
     */
    auto data = iteratorDataFromStringWithPos( str, str.cend() );
    REQUIRE( data.position == str.cend() );

    /*
     * Code point |ĵ|
     * Surrogate  | |
     *             ^
     */
    data.decrement();
    REQUIRE( data.position == str.cbegin() );
  }

  SECTION("Code point requiring 2 UTF-16 units: 𐐅")
  {
    const QString str = QString::fromUtf8("𐐅");

    /*
     * Code point | 𐐅 |
     * Surrogate  |H|L|
     *                 ^
     */
    auto data = iteratorDataFromStringWithPos( str, str.cend() );
    REQUIRE( data.position == str.cend() );

    /*
     * Code point | 𐐅 |
     * Surrogate  |H|L|
     *             ^
     */
    data.decrement();
    REQUIRE( data.position == str.cbegin() );
  }

  SECTION("A𐐅")
  {
    const QString str = QString::fromUtf8("A𐐅");

    /*
     * Code point |A| 𐐅 |
     * Surrogate  | |H|L|
     *                   ^
     */
    auto data = iteratorDataFromStringWithPos( str, str.cend() );
    REQUIRE( data.position == str.cend() );

    /*
     * Code point |A| 𐐅 |
     * Surrogate  | |H|L|
     *               ^
     */
    data.decrement();
    REQUIRE( data.position == str.cbegin()+1 );

    /*
     * Code point |A| 𐐅 |
     * Surrogate  | |H|L|
     *             ^
     */
    data.decrement();
    REQUIRE( data.position == str.cbegin() );
  }

  SECTION("𐐅A")
  {
    const QString str = QString::fromUtf8("𐐅A");

    /*
     * Code point | 𐐅 |A|
     * Surrogate  |H|L| |
     *                   ^
     */
    auto data = iteratorDataFromStringWithPos( str, str.cend() );
    REQUIRE( data.position == str.cend() );

    /*
     * Code point | 𐐅 |A|
     * Surrogate  |H|L| |
     *                 ^
     */
    data.decrement();
    REQUIRE( data.position == str.cbegin()+2 );

    /*
     * Code point | 𐐅 |A|
     * Surrogate  |H|L| |
     *             ^
     */
    data.decrement();
    REQUIRE( data.position == str.cbegin() );
  }

  SECTION("𐐅𝛀 (U+10405 U+1D6C0)")
  {
    const QString str = QString::fromUtf8("𐐅𝛀");

    /*
     * Code point | 𐐅 | 𝛀 |
     * Surrogate  |H|L|H|L|
     *                     ^
     */
    auto data = iteratorDataFromStringWithPos( str, str.cend() );
    REQUIRE( data.position == str.cend() );

    /*
     * Code point | 𐐅 | 𝛀 |
     * Surrogate  |H|L|H|L|
     *                 ^
     */
    data.decrement();
    REQUIRE( data.position == str.cbegin()+2 );

    /*
     * Code point | 𐐅 | 𝛀 |
     * Surrogate  |H|L|H|L|
     *             ^
     */
    data.decrement();
    REQUIRE( data.position == str.cbegin() );
  }
}

TEST_CASE("Impl_extractCodePoint")
{
  SECTION("A")
  {
    const QString str = QLatin1String("A");
    auto data = iteratorDataFromString(str);

    data.extractCodePoint();
    REQUIRE( data.value == U'A' );
  }

  SECTION("AB")
  {
    const QString str = QLatin1String("AB");
    auto data = iteratorDataFromString(str);

    data.extractCodePoint();
    REQUIRE( data.value == U'A' );

    data.increment();
    data.extractCodePoint();
    REQUIRE( data.value == U'B' );
  }

  SECTION("ĵ")
  {
    const QString str = QString::fromUtf8("ĵ");
    auto data = iteratorDataFromString(str);

    data.extractCodePoint();
    REQUIRE( data.value == U'ĵ' );
  }

  SECTION("𐐅")
  {
    const QString str = QString::fromUtf8("𐐅");
    auto data = iteratorDataFromString(str);

    data.extractCodePoint();
    REQUIRE( data.value == U'𐐅' );
  }

  SECTION("A𐐅")
  {
    const QString str = QString::fromUtf8("A𐐅");
    auto data = iteratorDataFromString(str);

    data.extractCodePoint();
    REQUIRE( data.value == U'A' );

    data.increment();
    data.extractCodePoint();
    REQUIRE( data.value == U'𐐅' );
  }

  SECTION("𐐅A")
  {
    const QString str = QString::fromUtf8("𐐅A");
    auto data = iteratorDataFromString(str);

    data.extractCodePoint();
    REQUIRE( data.value == U'𐐅' );

    data.increment();
    data.extractCodePoint();
    REQUIRE( data.value == U'A' );
  }

  SECTION("𐐅𝛀 (U+10405 U+1D6C0)")
  {
    const QString str = QString::fromUtf8("𐐅𝛀");
    auto data = iteratorDataFromString(str);

    data.extractCodePoint();
    REQUIRE( data.value == U'𐐅' );

    data.increment();
    data.extractCodePoint();
    REQUIRE( data.value == U'𝛀' );
  }
}

/*
 * Iterator interface tests
 */

TEST_CASE("construct")
{
  SECTION("Begin from QString::const_iterator, A")
  {
    const QString str = QLatin1String("A");
        QStringConstIterator it( str.cbegin(), str.cend() );
    REQUIRE( *it == U'A' );
  }

  SECTION("End from QString::const_iterator, A")
  {
    const QString str = QLatin1String("A");
        QStringConstIterator it( str.cend(), str.cend() );
  }

  SECTION("Begin from QString::iterator, A")
  {
    QString str = QLatin1String("A");
        QStringConstIterator it( str.begin(), str.end() );
    REQUIRE( *it == U'A' );
  }

  SECTION("End from QString::iterator, A")
  {
    QString str = QLatin1String("A");
        QStringConstIterator it( str.end(), str.end() );
  }
}

/*
 * Tests for LegacyIterator requirements
 */

static_assert( std::is_copy_constructible<QStringConstIterator>::value , "" );
static_assert( std::is_copy_assignable<QStringConstIterator>::value , "" );
static_assert( std::is_destructible<QStringConstIterator>::value , "" );

TEST_CASE("copy_construct")
{
  SECTION("A")
  {
    const QString str = QLatin1String("A");
        QStringConstIterator a( str.cbegin(), str.cend() );
    REQUIRE( *a == U'A' );

        QStringConstIterator b(a);
    REQUIRE( *b == U'A' );
  }

  SECTION("AB")
  {
    const QString str = QLatin1String("AB");
        QStringConstIterator a( str.cbegin(), str.cend() );
    REQUIRE( *a == U'A' );

        QStringConstIterator b(a);
    REQUIRE( *b == U'A' );
  }

  SECTION("ABC")
  {
    const QString str = QLatin1String("ABC");
        QStringConstIterator a( str.cbegin(), str.cend() );
    REQUIRE( *a == U'A' );

        QStringConstIterator b(a);
    REQUIRE( *b == U'A' );
  }

  SECTION("ö")
  {
    const QString str = QString::fromUtf8("ö");
        QStringConstIterator a( str.cbegin(), str.cend() );
    REQUIRE( *a == U'ö' );

        QStringConstIterator b(a);
    REQUIRE( *b == U'ö' );
  }

  SECTION("𐐅")
  {
    const QString str = QString::fromUtf8("𐐅");
        QStringConstIterator a( str.cbegin(), str.cend() );
    REQUIRE( *a == U'𐐅' );

        QStringConstIterator b(a);
    REQUIRE( *b == U'𐐅' );
  }
}

TEST_CASE("assign")
{
  const QString str = QLatin1String("ABCD");
    QStringConstIterator b;

    QStringConstIterator a( str.cbegin(), str.cend() );
  REQUIRE( *a == U'A' );
  b = a;
  REQUIRE( *b == U'A' );
}

TEST_CASE("dereference")
{
  const QString str = QLatin1String("ABCD");
    QStringConstIterator it( str.cbegin(), str.cend() );

  REQUIRE( *it == U'A' );
}

TEST_CASE("pre-increment")
{
  SECTION("AB")
  {
    const QString str = QLatin1String("AB");
        QStringConstIterator it( str.cbegin(), str.cend() );

    ++it;
    REQUIRE( *it == U'B' );
  }

  SECTION("A𐐅")
  {
    const QString str = QString::fromUtf8("A𐐅");
        QStringConstIterator it( str.cbegin(), str.cend() );

    ++it;
    REQUIRE( *it == U'𐐅' );
  }

  SECTION("𐐅A")
  {
    const QString str = QString::fromUtf8("𐐅A");
        QStringConstIterator it( str.cbegin(), str.cend() );

    ++it;
    REQUIRE( *it == U'A' );
  }
}

/*
 * Tests for LegacyInputIterator requirements
 */

TEST_CASE("comparison")
{
  const QString str = QLatin1String("ABCD");
    QStringConstIterator a( str.cbegin(), str.cend() );
  auto b = a;

  REQUIRE( a == b );
  REQUIRE( !(a != b) );
}

TEST_CASE("post-increment")
{
  const QString str = QLatin1String("ABCD");
    QStringConstIterator it( str.cbegin(), str.cend() );

  it++;
  REQUIRE( *it == U'B' );
}

/*
 * Tests for LegacyForwardIterator requirements
 */

static_assert( std::is_default_constructible<QStringConstIterator>::value , "" );

TEST_CASE("multipass")
{
  const QString str = QLatin1String("ABCD");
    QStringConstIterator a( str.cbegin(), str.cend() );
  auto b = a;

  REQUIRE( a == b );
  REQUIRE( *a == U'A' );
  REQUIRE( *b == U'A' );

  ++b;
  REQUIRE( a != b );
  REQUIRE( *a == U'A' );
  REQUIRE( *b == U'B' );
}

/*
 * Tests for LegacyBidirectionalIterator requirements
 */

TEST_CASE("decrement")
{
  const QString str = QLatin1String("ABCD");
    QStringConstIterator it( str.cbegin(), str.cend() );

  ++it;
  ++it;
  REQUIRE( *it == U'C' );

  --it;
  REQUIRE( *it == U'B' );
  it--;
  REQUIRE( *it == U'A' );

  SECTION("AB")
  {
    const QString str = QLatin1String("AB");
        QStringConstIterator it( str.cbegin(), str.cend() );
    ++it;
    REQUIRE( *it == U'B' );

    --it;
    REQUIRE( *it == U'A' );

    ++it;
    REQUIRE( *it == U'B' );

    it--;
    REQUIRE( *it == U'A' );
  }

  SECTION("A𐐅")
  {
    const QString str = QString::fromUtf8("A𐐅");
        QStringConstIterator it( str.cbegin(), str.cend() );
    ++it;
    REQUIRE( *it == U'𐐅' );

    --it;
    REQUIRE( *it == U'A' );
  }

  SECTION("𐐅A")
  {
    const QString str = QString::fromUtf8("𐐅A");
        QStringConstIterator it( str.cbegin(), str.cend() );
    ++it;
    REQUIRE( *it == U'A' );

    --it;
    REQUIRE( *it == U'𐐅' );
  }
}

/*
 * Other tests
 */

TEST_CASE("Unicode")
{
  SECTION("A")
  {
    const QString str = QString::fromUtf8("A");
        QStringConstIterator it( str.cbegin(), str.cend() );
    REQUIRE( *it == U'A' );
  }

  SECTION("ö")
  {
    const QString str = QString::fromUtf8("ö");
        QStringConstIterator it( str.cbegin(), str.cend() );
    REQUIRE( *it == U'ö' );
  }

  SECTION("ĵ")
  {
    const QString str = QString::fromUtf8("ĵ");
        QStringConstIterator it( str.cbegin(), str.cend() );
    REQUIRE( *it == U'ĵ' );
  }

  SECTION("�")
  {
    const QString str = QString::fromUtf8("�");
        QStringConstIterator it( str.cbegin(), str.cend() );
    REQUIRE( *it == U'�' );
  }

  SECTION("𐀀")
  {
    const QString str = QString::fromUtf8("𐀀");
        QStringConstIterator it( str.cbegin(), str.cend() );
    REQUIRE( *it == U'𐀀' );
  }

  SECTION("𐐅")
  {
    const QString str = QString::fromUtf8("𐐅");
        QStringConstIterator it( str.cbegin(), str.cend() );
    REQUIRE( *it == U'𐐅' );
  }
}
