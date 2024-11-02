/*
 * Copyright Philippe Steinmann 2020 - 2024.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#include <Mdt/PlainText/CsvFileReader>
#include <iostream>
#include <vector>
#include <string>

void printRecord(const std::vector<std::string> & record)
{
  if( record.empty() ){
    return;
  }
  std::cout << record[0];
  for(uint col = 1; col < record.size(); ++col){
    std::cout << '|' << record[col];
  }
}

int main()
{
  Mdt::PlainText::CsvFileReader reader;
  reader.setFilePath(TEST_FILE);
  reader.open();

  while( !reader.atEnd() ){
    printRecord( reader.readLine() );
    std::cout << std::endl;
  }
}
