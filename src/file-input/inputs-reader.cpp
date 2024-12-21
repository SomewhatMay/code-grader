// #include <file-input/inputs-reader.h>
#include <globals.h>

#include <file-inupt/inputs-reader-internal.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using json = nlohmann::json;

namespace fio {
std::vector<test_case> get_test_cases(const std::string& question_id);

}  // namespace fio

namespace fio::internal {
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
  if (raw.is_array()) {
    std::string parsed = "";

    for (auto it = raw.begin(); it != raw.end(); it++) {
      if (it != raw.begin()) {
        parsed += '\n';
      }

      if (it->is_string() || it->is_number()) {
        parsed += it->is_string() ? std::string(*it) : to_string(*it);
      } else {
        return zeus::unexpected("element " + std::to_string(it - raw.begin()) +
                                " is unparsable in test case");
      }
    }

    return parsed;
  } else if (raw.is_string() || raw.is_number()) {
    return raw.is_string() ? std::string(raw) : to_string(raw);
  } else {
    return zeus::unexpected("data is unparsable");
  }
}

fio::test_case parse_test_case(const json& entry) {
  fio::test_case current_case;
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

std::vector<fio::test_case> parse_test_cases(const json& data) {
  std::vector<fio::test_case> test_cases;

  for (auto& entry : data) {
    test_cases.push_back(parse_test_case(entry));
  }

  return test_cases;
}
}  // namespace fio::internal