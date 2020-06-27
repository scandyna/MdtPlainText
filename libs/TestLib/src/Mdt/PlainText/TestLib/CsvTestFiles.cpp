/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include "CsvTestFiles.h"
#include <QDir>

namespace Mdt{ namespace PlainText{ namespace TestLib{

QString csvTestFilePath(const std::string & testFileName)
{
  return QDir::cleanPath( QString::fromLocal8Bit(TEST_FILES_DIR) + QLatin1Char('/') + QString::fromStdString(testFileName) );
}

}}} // namespace Mdt{ namespace PlainText{ namespace TestLib{
