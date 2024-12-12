#include "file-input.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "globals.h"
#include "string-utils.h"

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

 private:
  // the returned information from the parser. Empty if unsuccessful.
  std::string _data;
  // error information
  std::string _what;

 public:
  parse_result(bool status, std::string what, std::string data)
      : status(status), _data(std::move(data)), _what(std::move(what)) {}

  parse_result(std::string data)
      : status(true), _data(std::move(data)), _what("") {}

  parse_result(bool status, std::string what)
      : status(status), _data(""), _what(std::move(what)) {}

  std::string what() { return _what; }

  std::string data() { return _data; }
};

void malformed_error(const std::string question_id, const std::string &what) {
  std::cerr << "Malformed question '" << question_id << "': " << what << '\n';
}

parse_result get_title(const std::string &line) {
  if (line[0] == '#') {
    if (line[1] == '#') {
      return parse_result(false,
                          "Found standalone description tag. Did you mean to "
                          "use '#' instead of '##' to denote a title?");
    }

    std::string title = line.substr(1);
    ltrim(title);  // title is already trimmed on the right

    return parse_result(title);
  }
}

parse_result get_description(const std::string &line) {
  if (line[0] == '#' && line[1] == '#') {
    std::string desc = line.substr(2);
    ltrim(desc);  // title is already trimmed on the right

    return parse_result(desc);
  } else {
    return parse_result(false, "no-description");
  }
}

parse_result get_input(const std::string &line) {
  remove_all_whitespace(line);

  if (line[0] != 'i') {
    return parse_result(false, "Expected input list. Instead found '" +
                                   shorten_line(line) + "'");
  } else {
  }
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

    trim(line);

    // line contains information
    if (status == SEARCHING_FOR_TITLE) {
      parse_result title_result = get_title(line);

      if (title_result.status == true) {
        current_case.title = title_result.data();
        status = parse_status::IN_TITLE;
      } else {
        malformed_error(question_id, title_result.what());
        status = parse_status::ERROR;
      }
    }
  }

  return test_cases;
}