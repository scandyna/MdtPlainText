##############################################################
#  Copyright Philippe Steinmann 2020 - 2020.
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt)
##############################################################
include(MdtAddTest)

mdt_add_test(
  NAME ContainerCompareTest
  TARGET containerCompareTest
  DEPENDENCIES Mdt::PlainText_TestLib Mdt::Catch2Main
  SOURCE_FILES
    src/ContainerCompareTest.cpp
)
