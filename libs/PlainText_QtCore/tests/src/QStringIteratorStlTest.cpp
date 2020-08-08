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
#include "Mdt/PlainText/BoostSpiritQStringConstIterator.h"
#include <QString>
#include <QLatin1String>
#include <iterator>

using Mdt::PlainText::BoostSpiritQStringConstIterator;
using Mdt::PlainText::Impl::BoostSpiritQStringConstIteratorData;


TEST_CASE("std_copy")
{
  QString destination;

  SECTION("abcd")
  {
    const QString source = QLatin1String("abcd");
    BoostSpiritQStringConstIterator first( source.cbegin(), source.cend() );
    BoostSpiritQStringConstIterator last( source.cend(), source.cend() );
    std::copy( first, last, std::back_inserter(destination) );
    REQUIRE( destination == source );
  }

  SECTION("éöàäèü$£𐐅")
  {
    const QString source = QString::fromUtf8("éöàäèü$£𐐅");
    BoostSpiritQStringConstIterator first( source.cbegin(), source.cend() );
    BoostSpiritQStringConstIterator last( source.cend(), source.cend() );
    std::copy( first, last, std::back_inserter(destination) );
    REQUIRE( destination == source );
  }
}
