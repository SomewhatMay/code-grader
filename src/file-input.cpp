#include "file-input.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

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

/////////////////////////////////////
// Parser
/////////////////////////////////////

enum parse_status {
  SEARCHING_FOR_TITLE,
  IN_TITLE,  // Either looking for description or inputs
  INPUT_FOUND,
  OUTPUT_FOUND,
  ERROR
};

struct parse_result {
  // whether the result was a success.
  bool status;

  // the returned information from the parser. Empty if unsuccessful.
  std::string data;

 private:
  // error information
  std::string _what;

 public:
  std::string what() { return _what; }
};

void malformed_error(const std::string question_id, const std::string &what) {
  std::cerr << "Malformed question '" << question_id << "': " << what << '\n';
}

std::string remove_all_whitespace(std::string line) {
  auto new_end = std::remove_if(line.begin(), line.end(), [](char x) {
    return (!std::isprint(x) || x == ' ');
  });
  line.erase(new_end, line.end());
  return line;
}

parse_result get_title(const std::string &line) {
  // find hashtag

  auto title_tag = std::find(line.cbegin(), line.cend(), '#');
}

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
  test_case current_case;
  while (status != parse_status::ERROR && std::getline(question_file, line)) {
    // skip if line is empty
    std::string printable_only_line = remove_all_whitespace(line);
    if (printable_only_line.length() == 0) {
      continue;
    }

    // line contains information
    if (status == SEARCHING_FOR_TITLE) {
      parse_result title_result = get_title(line);

      if (title_result.status == true) {
        current_case.title = title_result.data;
        status = parse_status::IN_TITLE;
      } else {
        malformed_error(question_id, title_result.what());
        status = parse_status::ERROR;
      }
    }
  }

  return test_cases;
}