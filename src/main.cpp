#include <iostream>
#include <string>
#include <vector>

#include "file-input.h"
#include "globals.h"

using std::cout, std::string, std::vector;

int main() {
  vector<string> question_list = get_question_list();
  cout << "Questions: \n";
  for (const auto &question_id : question_list) {
    cout << question_id << '\n';
  }
  return 0;
}
