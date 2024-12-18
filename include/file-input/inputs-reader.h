#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

/**
 * Contain the format of a test case as defined
 * in the question files.
 */
struct test_case {
  std::string title;
  std::string description;
  std::string inputs;
  std::string outputs;
};

nlohmann::json read_questions_file(const std::string& question_id);

std::vector<test_case> parse_test_cases(const json& data);

/**
 * Return a vector of test cases in the question with name
 * `question_id`.
 *
 * This function does not throw. If the test case file is malformed
 * and cannot be parsed, it will return an empty vector and output
 * the .what() in the stdout.
 */
std::vector<test_case> get_test_cases(const std::string& question_id);

