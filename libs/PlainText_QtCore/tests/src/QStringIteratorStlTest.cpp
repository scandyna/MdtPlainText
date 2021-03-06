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
#include "Mdt/PlainText/QStringUnicodeConstIterator.h"
#include "Mdt/PlainText/QStringUnicodeBackInsertIterator.h"
#include <QString>
#include <QLatin1String>
#include <iterator>

using Mdt::PlainText::QStringUnicodeConstIterator;
using Mdt::PlainText::QStringUnicodeBackInsertIterator;


TEST_CASE("std_copy")
{
  QString destination;

  SECTION("abcd")
  {
    const QString source = QLatin1String("abcd");
    QStringUnicodeConstIterator first( source.cbegin(), source.cend() );
    QStringUnicodeConstIterator last( source.cend(), source.cend() );
    std::copy( first, last, QStringUnicodeBackInsertIterator(destination) );
    REQUIRE( destination == source );
  }

  SECTION("éöàäèü$£𐐅")
  {
    const QString source = QString::fromUtf8("éöàäèü$£𐐅");
    QStringUnicodeConstIterator first( source.cbegin(), source.cend() );
    QStringUnicodeConstIterator last( source.cend(), source.cend() );
    std::copy( first, last, QStringUnicodeBackInsertIterator(destination) );
    REQUIRE( destination == source );
  }
}

TEST_CASE("std_fill_n")
{
  QString str;

  SECTION("5 𝛀")
  {
    std::fill_n( QStringUnicodeBackInsertIterator(str), 5, U'\U0001D6C0' );
    REQUIRE( str == QString::fromUtf8("𝛀𝛀𝛀𝛀𝛀") );
  }
}
