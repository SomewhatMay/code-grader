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
std::vector<test_case> get_test_cases(const std::string& question_id);

//// Internal structs, only to be used for tests

/**
 * Information returned to the main thread about the parse attempt.
 */
struct parse_result {
 public:
  /**
   * Whether or not the parse attempt was successful
   */
  bool status = false;

 private:
  /**
   * Cleaned parsed data.
   */
  std::string _data;

  /**
   * Contains any error information - not empty iff status == false.
   */
  std::string _what;

 public:
  parse_result(bool status, std::string data, std::string what)
      : status(status), _data(data), _what(what) {}

  parse_result(bool status, std::string what)
      : status(status), _what(what), _data("") {}

  parse_result(std::string data) : status(true), _what(""), _data(data) {}

  std::string what() { return _what; }

  std::string data() { return _data; }
};