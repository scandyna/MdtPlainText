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
#include "QCsvGrammarTestCommon.h"

TEST_CASE("FieldColumnRule")
{
  QString result;
  CsvParserSettings csvSettings;

  SECTION("empty")
  {
    const QString source = QLatin1String("");
    result = parseFieldColumn(source, csvSettings);
    REQUIRE( result == source );
  }

  SECTION("A")
  {
    const QString source = QLatin1String("A");
    result = parseFieldColumn(source, csvSettings);
    REQUIRE( result == source );
  }

  SECTION("\"A\"")
  {
    result = parseFieldColumn(QLatin1String("\"A\""), csvSettings);
    REQUIRE( result == QLatin1String("A") );
  }

  SECTION("AB")
  {
    const QString source = QLatin1String("AB");
    result = parseFieldColumn(source, csvSettings);
    REQUIRE( result == source );
  }

  SECTION("ABCD")
  {
    const QString source = QLatin1String("ABCD");
    result = parseFieldColumn(source, csvSettings);
    REQUIRE( result == source );
  }

  SECTION("\"ABCD\"")
  {
    result = parseFieldColumn(QLatin1String("\"ABCD\""), csvSettings);
    REQUIRE( result == QLatin1String("ABCD") );
  }

  SECTION("\"A\"\"BC\"\"D\"")
  {
    result = parseFieldColumn(QLatin1String("\"A\"\"BC\"\"D\""), csvSettings);
    REQUIRE( result == QLatin1String("A\"BC\"D") );
  }

  SECTION("\"A,B\"")
  {
    result = parseFieldColumn(QLatin1String("\"A,B\""), csvSettings);
    REQUIRE( result == QLatin1String("A,B") );
  }

  SECTION("éöàäèü$£")
  {
    const QString source = QString::fromUtf8("éöàäèü$£");
    result = parseFieldColumn(source, csvSettings);
    REQUIRE( result == source );
  }

  SECTION("\"éöàäèü$£\"")
  {
    result = parseFieldColumn(QString::fromUtf8("\"éöàäèü$£\""), csvSettings);
    REQUIRE( result == QString::fromUtf8("éöàäèü$£") );
  }

  SECTION("a𐐅ö")
  {
    const QString source = QString::fromUtf8("a𐐅ö");
    result = parseFieldColumn(source, csvSettings);
    REQUIRE( result == source );
  }

  SECTION("\"a𐐅ö\"")
  {
    result = parseFieldColumn(QString::fromUtf8("\"a𐐅ö\""), csvSettings);
    REQUIRE( result == QString::fromUtf8("a𐐅ö") );
  }

  SECTION("\"a𐐅,ö\"")
  {
    result = parseFieldColumn(QString::fromUtf8("\"a𐐅,ö\""), csvSettings);
    REQUIRE( result == QString::fromUtf8("a𐐅,ö") );
  }

}
