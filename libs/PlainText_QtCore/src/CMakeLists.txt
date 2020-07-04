##############################################################
#  Copyright Philippe Steinmann 2020 - 2020.
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt)
##############################################################
include(GenerateExportHeader)
include(MdtInstallLibrary)

add_library(Mdt_PlainText_QtCore
  Mdt/PlainText/BoostSpiritQStringContainer.cpp
  Mdt/PlainText/BoostSpiritQStringConstIterator.cpp
  Mdt/PlainText/QTextFileInputConstIteratorSharedData.cpp
  Mdt/PlainText/QTextFileInputConstIterator.cpp
  Mdt/PlainText/BoostSpiritQTextFileInputConstIterator.cpp
  Mdt/PlainText/QCsvFileReaderTemplate.cpp
  Mdt/PlainText/QCsvFileReader.cpp
)
add_library(Mdt::PlainText_QtCore ALIAS Mdt_PlainText_QtCore)

# At least boost::iterator_adaptor and boost::iterator_facade
# are exposed in the public API
target_link_libraries(Mdt_PlainText_QtCore
  PUBLIC
    Boost::boost
    Mdt::PlainText Qt5::Core
)

if(BUILD_USE_IPO_LTO)
  set_target_properties(Mdt_PlainText_QtCore
    PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE
  )
endif()

target_include_directories(Mdt_PlainText_QtCore
  PUBLIC
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

if(BOOST_SPIRIT_DEBUG)
  target_compile_definitions(Mdt_PlainText_QtCore
    PRIVATE
      BOOST_SPIRIT_DEBUG
  )
endif()

generate_export_header(Mdt_PlainText_QtCore)

mdt_install_library(
  TARGET Mdt_PlainText_QtCore
  RUNTIME_DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY_DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE_DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES_DIRECTORY .
  INCLUDES_FILE_WITHOUT_EXTENSION
  ADDITIONAL_INCLUDES_FILES "${CMAKE_CURRENT_BINARY_DIR}/mdt_plaintext_qtcore_export.h"
  INCLUDES_DESTINATION ${MDT_INSTALL_INCLUDEDIR}
  EXPORT_NAME PlainText_QtCore
  EXPORT_NAMESPACE Mdt${PROJECT_VERSION_MAJOR}::
  INSTALL_NAMESPACE ${MDT_INSTALL_PACKAGE_NAME}
  FIND_PACKAGE_PATHS ..
  INSTALL_IS_UNIX_SYSTEM_WIDE ${MDT_INSTALL_IS_UNIX_SYSTEM_WIDE}
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  VERSION_COMPATIBILITY ExactVersion
  RUNTIME_COMPONENT Mdt_PlainText_QtCore_Runtime
  DEVELOPMENT_COMPONENT Mdt_PlainText_QtCore_Dev
)
