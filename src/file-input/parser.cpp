#include "file-input/parser.h"

#include <algorithm>
#include <fstream>
#include <iostream>

#include "globals.h"
#include "string-utils.h"

enum parse_status { SEARCH_TEST, IN_TEST, IN_INPUT, IN_OUTPUT, ERROR };

void malformed_error(const std::string question_id, const int& line_number,
                     const std::string& what) {
  std::cerr << "Malformed question '" << question_id << "' [line "
            << line_number << "] : " << what << '\n';
}

parse_result get_heading(std::string line) {
  ltrim(line);

  if (line[0] == '#') {
    std::string title = line.substr(1);
    ltrim(title);

    return parse_result(title);
  }

  return parse_result(false, "expected test case title");
}

/**
 * Line must be a valid description line.
 */
parse_result get_desc(std::string line) { ltrim(line); }

std::vector<test_case> get_test_cases(std::string& question_id) {
  std::vector<test_case> test_cases;

  // Open the file stream
  std::ifstream question_file(std::string(globals::QUESTIONS_PATH) +
                              question_id);

  if (!question_file) {
    std::cerr << "Unable to open file with path " << question_id;
    return test_cases;
  }

  std::string line;
  int line_number = 0;
  parse_status current_status = parse_status::SEARCH_TEST;
  parse_result result(
      false,
      "fatal: code not executed");  // most recent parse_result from parsing
  test_case current_case;
  while (getline(question_file, line) &&
         current_status != parse_status::ERROR) {
    line_number++;

    // Skip line if it is empty
    std::string printable_only_line = remove_all_whitespace(line);
    if (printable_only_line.length() == 0) {
      continue;
    }

    if (current_status == parse_status::SEARCH_TEST) {
      result = get_heading(line);

      if (!result.status) {
        current_status = parse_status::ERROR;
        break;
      }

      current_case.title = result.data();
      current_status = parse_status::IN_INPUT;
    } else if (current_status == parse_status::IN_INPUT) {
      std::string trimmed_line = line;
      ltrim(line);

      // If line starts with "desc"...
      if (trimmed_line.rfind("desc", 0) == 0) {
        parse_result result = get_desc(line);
      }
    }

    // TODO remember to append the case
  }

  if (current_status == parse_status::ERROR) {
    malformed_error(question_id, line_number, result.what());
    return std::vector<test_case>();
  } else {
    return test_cases;
  }
}