#pragma once

#include <string>
#include <vector>

/**
 * Contain the format of a test case as defined
 * in the question files.
 */
struct test_case {
  std::string title;
  std::string description;
  std::vector<std::string> inputs;
  std::vector<std::string> outputs;
};

/**
 * Return a vector of `question_id`s based on the names
 * of each question in the resources/questions folder.
 */
std::vector<std::string> get_question_list();

/**
 * Return a vector of test cases in the question with name
 * `question_id`.
 *
 * This function does not throw. If the test case file is malformed
 * and cannot be parsed, it will return an empty vector and output
 * the .what() in the stdout.
 */
std::vector<test_case> get_test_cases(std::string question_id);