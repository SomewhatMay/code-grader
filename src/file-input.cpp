#include "file-input.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "globals.h"

namespace fs = std::filesystem;

std::vector<std::string> get_question_list() {
  // Change this line to use an absolute or relative path as needed
  std::vector<std::string> question_list;
  fs::directory_iterator iterator(globals::QUESTIONS_PATH);

  for (const auto &entry : iterator) {
    if (entry.is_directory()) {
      std::string question_id = entry.path().filename().string();
      question_list.push_back(question_id);
    }
  }

  return question_list;
}

enum parse_status {
  SEARCHING_FOR_TITLE,
  IN_TITLE,  // Either looking for description or inputs
  INPUT_FOUND,
  OUTPUT_FOUND,
};

std::vector<test_case> get_test_cases(std::string question_id) {
  std::vector<test_case> test_cases;
  std::ifstream question_file(std::string(globals::QUESTIONS_PATH) +
                              question_id);

  if (!question_file) {
    std::cerr << "Unable to open file with path " << question_id;
    return test_cases;
  }

  std::string line;
  parse_status status = SEARCHING_FOR_TITLE;
  while (std::getline(question_file, line)) {
    if (status == SEARCHING_FOR_TITLE) {
      auto titleTag = std::find(line.cbegin(), line.cend(), '#');
      
      // Ensure that this is not a description tag instead
      auto descTag = std::find(titleTag + 1, line.cend(), '#');
    }
  }
}