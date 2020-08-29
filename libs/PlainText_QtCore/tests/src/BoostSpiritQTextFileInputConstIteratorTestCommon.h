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
#include "Mdt/PlainText/BoostSpiritQTextFileInputConstIterator.h"
#include "Mdt/PlainText/BoostSpiritQiQStringSupport"
#include "Mdt/PlainText/TestLib/TextFileUtils.h"
#include <boost/spirit/include/support_multi_pass.hpp>
#include <QTemporaryFile>
#include <QFile>
#include <QLatin1String>
#include <QLatin1Char>
#include <boost/spirit/include/qi.hpp>
#include <type_traits>
#include <algorithm>

using namespace Mdt::PlainText;

bool openTextFileReadOnly(QFile & file)
{
  return file.open(QIODevice::ReadOnly | QIODevice::Text);
}

template<typename Grammar, typename Result>
bool parse(QFile & file, const Grammar & grammar, Result & destination)
{
  using boost::spirit::multi_pass;
  using boost::spirit::make_default_multi_pass;

  using MultiPassIterator = multi_pass<BoostSpiritQTextFileInputConstIterator>;

  MultiPassIterator first = make_default_multi_pass( BoostSpiritQTextFileInputConstIterator(&file, "UTF-8") );
  MultiPassIterator last = make_default_multi_pass( BoostSpiritQTextFileInputConstIterator() );

  return boost::spirit::qi::parse(first, last, grammar, destination);
}

bool writeTextFile(QFile & file, const QString & content)
{
  return Mdt::PlainText::TestLib::writeTextFileUtf8(file, content);
}
