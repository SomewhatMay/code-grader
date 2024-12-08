#include <iostream>
#include <string>

#include "file-io/file-input.h"
#include "globals.h"

using std::cout, std::string;

int main() {
  string greeting = get_greeting();
  cout << greeting << '\n';
  cout << constants::QUESTIONS_PATH << '\n';

  return 0;
}