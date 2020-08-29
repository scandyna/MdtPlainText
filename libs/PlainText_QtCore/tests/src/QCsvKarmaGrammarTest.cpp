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
#include "QCsvKarmaGrammarTestCommon.h"

TEST_CASE("UnprotectedField")
{
  QString result;
  CsvGeneratorSettings csvSettings;

  SECTION("empty")
  {
    result = generateUnprotectedField(QLatin1String(""), csvSettings);
    REQUIRE( result.isEmpty() );
  }

  SECTION("A")
  {
    result = generateUnprotectedField(QLatin1String("A"), csvSettings);
    REQUIRE( result == QLatin1String("A") );
  }

  SECTION("AB")
  {
    result = generateUnprotectedField(QLatin1String("AB"), csvSettings);
    REQUIRE( result == QLatin1String("AB") );
  }

  SECTION("ABC")
  {
    result = generateUnprotectedField(QLatin1String("ABC"), csvSettings);
    REQUIRE( result == QLatin1String("ABC") );
  }

  SECTION("ö")
  {
    result = generateUnprotectedField(QString::fromUtf8("ö"), csvSettings);
    REQUIRE( result == QString::fromUtf8("ö") );
  }

  SECTION("ĵ")
  {
    result = generateUnprotectedField(QString::fromUtf8("ĵ"), csvSettings);
    REQUIRE( result == QString::fromUtf8("ĵ") );
  }

  SECTION("𐐅")
  {
    result = generateUnprotectedField(QString::fromUtf8("𐐅"), csvSettings);
    REQUIRE( result == QString::fromUtf8("𐐅") );
  }

  SECTION("a𐐅ö")
  {
    result = generateUnprotectedField(QString::fromUtf8("a𐐅ö"), csvSettings);
    REQUIRE( result == QString::fromUtf8("a𐐅ö") );
  }

  SECTION("a𐐅,ö")
  {
    REQUIRE( generateUnprotectedFieldFails(QString::fromUtf8("a𐐅,ö"), csvSettings) );
  }
}

TEST_CASE("UnprotectedField_EXP")
{
  QString result;
  CsvGeneratorSettings csvSettings;

  SECTION("Add EXP")
  {
    csvSettings.setAddExp(true);

    SECTION("A")
    {
      result = generateUnprotectedField(QLatin1String("A"), csvSettings);
      REQUIRE( result == QLatin1String("~A") );
    }

    SECTION("a𐐅ö")
    {
      result = generateUnprotectedField(QString::fromUtf8("a𐐅ö"), csvSettings);
      REQUIRE( result == QString::fromUtf8("~a𐐅ö") );
    }
  }

  SECTION("Do not add EXP")
  {
    csvSettings.setAddExp(false);

    SECTION("A")
    {
      result = generateUnprotectedField(QLatin1String("A"), csvSettings);
      REQUIRE( result == QLatin1String("A") );
    }

    SECTION("a𐐅ö")
    {
      result = generateUnprotectedField(QString::fromUtf8("a𐐅ö"), csvSettings);
      REQUIRE( result == QString::fromUtf8("a𐐅ö") );
    }
  }
}

TEST_CASE("ProtectedField")
{
  QString result;
  CsvGeneratorSettings csvSettings;

  SECTION("A")
  {
    result = generateProtectedField(QLatin1String("A"), csvSettings);
    REQUIRE( result == QLatin1String("\"A\"") );
  }

  SECTION("AB")
  {
    result = generateProtectedField(QLatin1String("AB"), csvSettings);
    REQUIRE( result == QLatin1String("\"AB\"") );
  }

  SECTION("ABC")
  {
    result = generateProtectedField(QLatin1String("ABC"), csvSettings);
    REQUIRE( result == QLatin1String("\"ABC\"") );
  }

  SECTION("ö")
  {
    result = generateProtectedField(QString::fromUtf8("ö"), csvSettings);
    REQUIRE( result == QString::fromUtf8("\"ö\"") );
  }

  SECTION("ĵ")
  {
    result = generateProtectedField(QString::fromUtf8("ĵ"), csvSettings);
    REQUIRE( result == QString::fromUtf8("\"ĵ\"") );
  }

  SECTION("𐐅")
  {
    result = generateProtectedField(QString::fromUtf8("𐐅"), csvSettings);
    REQUIRE( result == QString::fromUtf8("\"𐐅\"") );
  }

  SECTION("a𐐅ö")
  {
    result = generateProtectedField(QString::fromUtf8("a𐐅ö"), csvSettings);
    REQUIRE( result == QString::fromUtf8("\"a𐐅ö\"") );
  }

  SECTION("a𐐅,ö")
  {
    result = generateProtectedField(QString::fromUtf8("a𐐅,ö"), csvSettings);
    REQUIRE( result == QString::fromUtf8("\"a𐐅,ö\"") );
  }
}

TEST_CASE("FieldColumn")
{
  QString result;
  CsvGeneratorSettings csvSettings;

  SECTION("empty")
  {
    result = generateFieldColumn(QLatin1String(""), csvSettings);
    REQUIRE( result == QLatin1String("") );
  }

  SECTION("A")
  {
    result = generateFieldColumn(QLatin1String("A"), csvSettings);
    REQUIRE( result == QLatin1String("A") );
  }

  SECTION("a𐐅ö")
  {
    result = generateFieldColumn(QString::fromUtf8("a𐐅ö"), csvSettings);
    REQUIRE( result == QString::fromUtf8("a𐐅ö") );
  }

  SECTION("a𐐅,ö")
  {
    result = generateFieldColumn(QString::fromUtf8("a𐐅,ö"), csvSettings);
    REQUIRE( result == QString::fromUtf8("\"a𐐅,ö\"") );
  }
}

TEST_CASE("CsvRecord")
{
  QStringList record;
  QString result;
  CsvGeneratorSettings csvSettings;
  csvSettings.setEndOfLine(EndOfLine::Lf);

  SECTION("A|B")
  {
    record = qStringListFromStdStringList({"A","B"});
    result = generateCsvRecord(record, csvSettings);
    REQUIRE( result == QLatin1String("A,B\n") );
  }

  SECTION("a|𐐅|ö")
  {
    record = qStringListFromStdStringList({"a","𐐅","ö"});
    result = generateCsvRecord(record, csvSettings);
    REQUIRE( result == QString::fromUtf8("a,𐐅,ö\n") );
  }

  SECTION("ab|c𐐅|ö")
  {
    record = qStringListFromStdStringList({"ab","c𐐅","ö"});
    result = generateCsvRecord(record, csvSettings);
    REQUIRE( result == QString::fromUtf8("ab,c𐐅,ö\n") );
  }

  SECTION("a,b|c,𐐅|ö")
  {
    record = qStringListFromStdStringList({"a,b","c,𐐅","ö"});
    result = generateCsvRecord(record, csvSettings);
    REQUIRE( result == QString::fromUtf8("\"a,b\",\"c,𐐅\",ö\n") );
  }

  SECTION("\"ab\"|\"c𐐅\"|ö")
  {
    record = qStringListFromStdStringList({"\"ab\"","\"c𐐅\"","ö"});
    result = generateCsvRecord(record, csvSettings);
    REQUIRE( result == QString::fromUtf8("\"\"\"ab\"\"\",\"\"\"c𐐅\"\"\",ö\n") );
  }
}
