#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

enum outputs_t {
  string_sequence,  // default
  floating_point
};

/**
 * Contain the format of a test case as defined
 * in the question files.
 */
struct test_case {
  std::string title;
  std::string description;
  std::string inputs;
  std::string outputs;

  outputs_t outputs_type = outputs_t::string_sequence;
  int round = 0;

  std::string stringify() {
    return "object<test_case>\nTitle: " + title + "\nDesc: " + description +
           "\nInputs: " + inputs + "\nOutputs" + outputs + "\n";
  }
};

nlohmann::json read_questions_file(const std::string& question_id);

std::vector<test_case> parse_test_cases(const nlohmann::json& data);

/**
 * Return a vector of test cases in the question with name
 * `question_id`.
 *
 * This function does not throw. If the test case file is malformed
 * and cannot be parsed, it will return an empty vector and output
 * the .what() in the stdout.
 */
std::vector<test_case> get_test_cases(const std::string& question_id);
