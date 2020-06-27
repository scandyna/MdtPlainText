/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_TEST_LIB_CONTAINER_COMPARE_H
#define MDT_PLAIN_TEXT_TEST_LIB_CONTAINER_COMPARE_H

#include <QString>
#include <string>
#include <vector>
#include <iostream>

namespace Mdt{ namespace PlainText{ namespace TestLib{

  template<typename Container>
  int containerSize(const Container & container)
  {
    return container.size();
  }

  bool stringMatches(const std::string & str, const std::string & reference)
  {
    return str == reference;
  }

  bool stringMatches(const QString & str, const std::string & reference)
  {
    return str.toStdString() == reference;
  }

  std::ostream & operator<<(std::ostream & stream, const QString & str)
  {
    return stream << str.toStdString();
  }

  template<typename Record>
  bool recordMatches(const Record & record, const std::vector<std::string> & referenceRecord)
  {
    if( containerSize(record) != containerSize(referenceRecord) ){
      std::cerr << "record size (" << containerSize(record) << ") is different than expected (" << containerSize(referenceRecord) << ")" << std::endl;
      return false;
    }

    for(int i = 0; i < containerSize(record); ++i){
      if( !stringMatches(record[i], referenceRecord[i]) ){
        std::cerr << "record[" << i << "] does not match:\n";
        std::cerr << " expected: " << referenceRecord[i] << '\n';
        std::cerr << "   result: " << record[i] << std::endl;
        return false;
      }
    }

    return true;
  }

  template<typename Table>
  bool tableMatches(const Table & table, const std::vector< std::vector<std::string> > & referenceTable)
  {
    if( containerSize(table) != containerSize(referenceTable) ){
      std::cerr << "table size (" << containerSize(table) << ") is different than expected (" << containerSize(referenceTable) << ")" << std::endl;
      return false;
    }

    for(int row = 0; row < containerSize(table); ++row){
      if( containerSize(table[row]) != containerSize(referenceTable[row]) ){
        std::cerr << "line " << row << ", record size (" << containerSize(table[row])
                  << ") is different than expected (" << containerSize(referenceTable[row]) << ")" << std::endl;
        return false;
      }
      for(int col = 0; col < containerSize(table[row]); ++col){
        if( !stringMatches(table[row][col], referenceTable[row][col]) ){
          std::cerr << "line " << row << ", record[" << col << "] does not match:";
          std::cerr << " expected: " << referenceTable[row][col] << '\n';
          std::cerr << "   result: " << table[row][col] << std::endl;
          return false;
        }
      }
    }

    return true;
  }

}}} // namespace Mdt{ namespace PlainText{ namespace TestLib{

#endif // #ifndef MDT_PLAIN_TEXT_TEST_LIB_CONTAINER_COMPARE_H
