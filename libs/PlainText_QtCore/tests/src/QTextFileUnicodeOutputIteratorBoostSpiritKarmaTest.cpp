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
#include "QTextFileOutputIteratorTestCommon.h"
#include "Mdt/PlainText/QTextFileUnicodeOutputIterator.h"
#include "Mdt/PlainText/BoostSpiritKarmaQStringSupport"

template<typename Rule>
bool generateToFile(const QString & source, const Rule & rule, QFile & file)
{
  const Mdt::PlainText::QStringUnicodeView sourceContainer(source);
  Mdt::PlainText::QTextFileUnicodeOutputIterator fileIterator(&file, "UTF-8");

  return boost::spirit::karma::generate(fileIterator, rule, sourceContainer);
}


TEST_CASE("generate_standard_char_")
{
  using boost::spirit::standard::char_;

  QTemporaryFile file;
  REQUIRE( openTextFileForWrite(file) );

  SECTION("*char_ A")
  {
    REQUIRE( generateToFile(QLatin1String("A"), *char_, file) );
    REQUIRE( readTextFileBack(file) == QLatin1String("A") );
  }

  SECTION("AB")
  {
    REQUIRE( generateToFile(QLatin1String("AB"), *char_, file) );
    REQUIRE( readTextFileBack(file) == QLatin1String("AB") );
  }

  SECTION("ABC")
  {
    REQUIRE( generateToFile(QLatin1String("ABC"), *char_, file) );
    REQUIRE( readTextFileBack(file) == QLatin1String("ABC") );
  }
}

TEST_CASE("generate_unicode_char_")
{
  using boost::spirit::unicode::char_;

  QTemporaryFile file;
  REQUIRE( openTextFileForWrite(file) );

  SECTION("*char_ A")
  {
    REQUIRE( generateToFile(QLatin1String("A"), *char_, file) );
    REQUIRE( readTextFileBack(file) == QString::fromUtf8("A") );
  }

  SECTION("ö")
  {
    REQUIRE( generateToFile(QString::fromUtf8("ö"), *char_, file) );
    REQUIRE( readTextFileBack(file) == QString::fromUtf8("ö") );
  }

  SECTION("ĵ")
  {
    REQUIRE( generateToFile(QString::fromUtf8("ĵ"), *char_, file) );
    REQUIRE( readTextFileBack(file) == QString::fromUtf8("ĵ") );
  }

  SECTION("𐐅")
  {
    REQUIRE( generateToFile(QString::fromUtf8("𐐅"), *char_, file) );
    REQUIRE( readTextFileBack(file) == QString::fromUtf8("𐐅") );
  }
}
