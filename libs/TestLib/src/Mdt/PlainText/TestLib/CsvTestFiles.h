/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_TEST_LIB_CSV_TEST_FILES_H
#define MDT_PLAIN_TEXT_TEST_LIB_CSV_TEST_FILES_H

#include "mdt_plaintext_testlib_export.h"
#include <QString>
#include <string>
#include <vector>

namespace Mdt{ namespace PlainText{ namespace TestLib{

  /*! \internal Get the path to a CSV test file
   */
  MDT_PLAINTEXT_TESTLIB_EXPORT
  QString csvTestFilePath(const std::string & testFileName);

  inline
  std::vector< std::vector<std::string> > Wikipedia_car_example_ReferenceTable()
  {
    return {
      {"Year","Make","Model","Description","Price"},
      {"1997","Ford","E350","ac, abs, moon","3000.00"},
      {"1999","Chevy","Venture \"Extended Edition\"","","4900.00"},
      {"1999","Chevy","Venture \"Extended Edition, Very Large\"","","5000.00"},
      {"1996","Jeep","Grand Cherokee","MUST SELL!\nair, moon roof, loaded","4799.00"}
    };
  }

  inline
  std::vector< std::vector<std::string> > Wikipedia_European_UK_example_ReferenceTable()
  {
    return{
      {"Year","Make","Model","Length"},
      {"1997","Ford","E350","2.35"},
      {"2000","Mercury","Cougar","2.38"}
    };
  }

  inline
  std::vector< std::vector<std::string> > Wikipedia_USA_UK_example_ReferenceTable()
  {
    return{
      {"Year","Make","Model","Length"},
      {"1997","Ford","E350","2,35"},
      {"2000","Mercury","Cougar","2,38"}
    };
  }

}}} // namespace Mdt{ namespace PlainText{ namespace TestLib{

#endif // #ifndef MDT_PLAIN_TEXT_TEST_LIB_CSV_TEST_FILES_H
