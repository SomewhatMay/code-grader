#include <iostream>
#include <string>
#include <vector>

#include "file-input.h"
#include "globals.h"

int main() {
  std::vector<std::string> question_list = get_question_list();
  std::cout << "Questions: \n";
  for (const auto &question_id : question_list) {
    std::cout << question_id << '\n';
  }
  return 0;
}
