#include <iostream>
#include <string>
#include <vector>

#include "file-retriever.h"
#include "globals.h"

int main() {
  std::vector<std::string> question_list = fio::get_question_list();
  std::cout << "Questions: \n";
  for (const auto &question_id : question_list) {
    std::cout << question_id << '\n';
  }
  return 0;
}
