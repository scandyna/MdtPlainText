##############################################################
#  Copyright Philippe Steinmann 2020 - 2020.
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt)
##############################################################
include(GenerateExportHeader)
include(MdtInstallLibrary)

add_library(Mdt_PlainText
  Mdt/PlainText/Grammar/Csv/Qi/SafeChar.cpp
  Mdt/PlainText/Grammar/Csv/Qi/Char.cpp
  Mdt/PlainText/Grammar/Csv/Qi/UnprotectedField.cpp
  Mdt/PlainText/Grammar/Csv/Qi/NonEmptyUnprotectedField.cpp
  Mdt/PlainText/Grammar/Csv/Qi/ProtectedField.cpp
  Mdt/PlainText/Grammar/Csv/Qi/FieldColumn.cpp
  Mdt/PlainText/Grammar/Csv/Qi/NonEmptyFieldColumn.cpp
  Mdt/PlainText/Grammar/Csv/Qi/CsvRecord.cpp
  Mdt/PlainText/Grammar/Csv/Qi/CsvFileLine.cpp
  Mdt/PlainText/Grammar/Csv/Qi/CsvFile.cpp
  Mdt/PlainText/Grammar/Csv/Karma/SafeChar.cpp
  Mdt/PlainText/Grammar/Csv/Karma/UnprotectedField.cpp
  Mdt/PlainText/Grammar/Csv/Karma/ProtectedField.cpp
  Mdt/PlainText/Grammar/Csv/Karma/FieldColumn.cpp
  Mdt/PlainText/Grammar/Csv/Karma/CsvRecord.cpp
  Mdt/PlainText/Grammar/Csv/Karma/CsvFile.cpp
  Mdt/PlainText/CsvParserSettings.cpp
  Mdt/PlainText/OpenFstream.cpp
  Mdt/PlainText/CsvFileReaderTemplate.cpp
  Mdt/PlainText/CsvFileReader.cpp
  Mdt/PlainText/CsvGeneratorSettings.cpp
  Mdt/PlainText/CsvFileWriterTemplate.cpp
  Mdt/PlainText/CsvFileWriter.cpp
  Mdt/PlainText/ContainerAliasViewConstIterator.cpp
  Mdt/PlainText/ContainerAliasView.cpp
)

if(UNIX)
  target_sources(Mdt_PlainText
    PRIVATE
      Mdt/PlainText/BasicFileInfo_unix.cpp
  )
endif()

# Set the native end of line
# target_compile_definitions(Mdt_PlainText
#   PUBLIC
#     MDT_PLAIN_TEXT_END_OF_LINE_LF=1 MDT_PLAIN_TEXT_END_OF_LINE_CRLF=2 MDT_PLAIN_TEXT_END_OF_LINE_CR=3
# )
if(WIN32 OR CYGWIN)
  target_compile_definitions(Mdt_PlainText PUBLIC MDT_PLAIN_TEXT_OS_WINDOWS=1)
elseif(UNIX)
  target_compile_definitions(Mdt_PlainText PUBLIC MDT_PLAIN_TEXT_OS_UNIX=1)
endif()

add_library(Mdt::PlainText ALIAS Mdt_PlainText)

target_link_libraries(Mdt_PlainText
  PRIVATE
    Boost::boost
)

target_compile_features(Mdt_PlainText PUBLIC cxx_std_14)

if(BUILD_USE_IPO_LTO)
  set_target_properties(Mdt_PlainText
    PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE
  )
endif()

target_include_directories(Mdt_PlainText
  PUBLIC
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

target_compile_definitions(Mdt_PlainText
  PUBLIC
    BOOST_SPIRIT_UNICODE
)

generate_export_header(Mdt_PlainText)

mdt_install_library(
  TARGET Mdt_PlainText
  RUNTIME_DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY_DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE_DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES_DIRECTORY .
  INCLUDES_FILE_WITHOUT_EXTENSION
  ADDITIONAL_INCLUDES_FILES "${CMAKE_CURRENT_BINARY_DIR}/mdt_plaintext_export.h"
  INCLUDES_DESTINATION ${MDT_INSTALL_INCLUDEDIR}
  EXPORT_NAME PlainText
  EXPORT_NAMESPACE Mdt${PROJECT_VERSION_MAJOR}::
  INSTALL_NAMESPACE ${MDT_INSTALL_PACKAGE_NAME}
  FIND_PACKAGE_PATHS ..
  INSTALL_IS_UNIX_SYSTEM_WIDE ${MDT_INSTALL_IS_UNIX_SYSTEM_WIDE}
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  VERSION_COMPATIBILITY ExactVersion
  RUNTIME_COMPONENT Mdt_PlainText_Runtime
  DEVELOPMENT_COMPONENT Mdt_PlainText_Dev
)
