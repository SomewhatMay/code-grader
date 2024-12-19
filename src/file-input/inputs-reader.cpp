#include <file-input/inputs-reader.h>
#include <globals.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using json = nlohmann::json;

json read_questions_file(const std::string& question_id) {
  std::string total_path = std::string(globals::QUESTIONS_PATH) + question_id;
  std::ifstream questions_file(total_path);

  if (questions_file) {
    std::cerr << "Unable to open questions file '" << total_path << "'\n";
    return json::array({});
  }

  json data = json::parse(questions_file);

  if (!data.is_array()) {
    std::cerr << "Unable to parse data in file. File '" << total_path << "'\n";
    return json::array({});
  }

  return data;
}

template <typename T>
struct result_t {
 private:
  bool status_;
  T data_;

 public:
  result_t(bool status, T data) : status_(status), data_(data) {}

  bool status() { return status_; }

  T data() { return data_; }
};

result_t<std::string> parse_io(const json& raw) {
  std::string parsed = "";

  if (raw.is_string()) {
    parsed = raw;
  } else if (raw.is_array()) {
    for (auto it = raw.begin(); it != raw.end(); it++) {
      if (it != raw.begin()) {
        parsed += '\n';
      }

      parsed += std::string(*it);
    }
  } else {
    return result_t<std::string>(false, "");
  }

  return result_t<std::string>(true, parsed);
}

test_case parse_test_case(const json& entry) {
  test_case current_case;
  current_case.title = entry.at("title");

  current_case.description =
      entry.at("description").is_string() ? entry.at("description") : "";

  auto raw_inputs = entry.at("inputs");
  std::string inputs = "";

  current_case.inputs = inputs;

  return current_case;
}

std::vector<test_case> parse_test_cases(const json& data) {
  std::vector<test_case> test_cases;

  for (auto& entry : data) {
    test_case current_case = parse_test_case(entry);
    test_cases.push_back(current_case);
  }

  return test_cases;
}

std::vector<test_case> get_test_cases(const std::string& question_id) {
  return std::vector<test_case>();
};