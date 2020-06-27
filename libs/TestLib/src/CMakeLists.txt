##############################################################
#  Copyright Philippe Steinmann 2020 - 2020.
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt)
##############################################################
include(GenerateExportHeader)

add_library(Mdt_PlainText_TestLib
  Mdt/PlainText/TestLib/ContainerCompare.cpp
)
add_library(Mdt::PlainText_TestLib ALIAS Mdt_PlainText_TestLib)

if(BUILD_USE_IPO_LTO)
  set_target_properties(Mdt_PlainText_TestLib
    PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE
  )
endif()

target_link_libraries(Mdt_PlainText_TestLib
  PUBLIC
    Mdt::PlainText Qt5::Core
)

target_include_directories(Mdt_PlainText_TestLib
  PUBLIC
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

generate_export_header(Mdt_PlainText_TestLib)
