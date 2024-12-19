#include <file-input/inputs-reader.h>
#include <globals.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <zeus/expected.hpp>

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

zeus::expected<std::string, std::string> parse_io(const json& raw) {
  if (raw.is_string()) {
    return raw;
  } else if (raw.is_number()) {
    return std::to_string(raw.is_number_float() ? (float)raw : (int)raw);
  } else if (raw.is_array()) {
    std::string parsed = "";

    for (auto it = raw.begin(); it != raw.end(); it++) {
      if (it != raw.begin()) {
        parsed += '\n';
      }

      if (it->is_string()) {
        parsed += *it;
      } else if (it->is_number()) {
        parsed += std::to_string(it->is_number_float() ? (float)*it : (int)*it);
      } else {
        return zeus::unexpected("element " + std::to_string(it - raw.begin()) +
                                " is unparsable in test case");
      }
    }

    return parsed;
  } else {
    return zeus::unexpected("raw is unparsable");
  }
}

test_case parse_test_case(const json& entry) {
  test_case current_case;
  current_case.title = entry.at("title");

  current_case.description =
      entry.at("description").is_string() ? entry.at("description") : "";

  zeus::expected<std::string, std::string> inputs =
      parse_io(entry.at("inputs"));
  if (inputs.has_value()) {
    current_case.inputs = *inputs;
  } else {
    std::cerr << "Unable to parse inputs for test case - " << inputs.error()
              << "\n";
  }

  zeus::expected<std::string, std::string> outputs =
      parse_io(entry.at("outputs"));
  if (outputs.has_value()) {
    current_case.outputs = *outputs;
  } else {
    std::cerr << "Unable to parse outputs for test case - " << outputs.error()
              << "\n";
  }

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