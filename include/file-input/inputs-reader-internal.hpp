#pragma once
#include "file-input/inputs-reader.h"

/**
 * Contains internal functions, only exposed for testing.
 */
namespace fio::internal {
nlohmann::json read_questions_file(const std::string& question_id);

zeus::expected<std::string, std::string> parse_io(const nlohmann::json& raw);

fio::test_case parse_test_case(const nlohmann::json& entry);

std::vector<fio::test_case> parse_test_cases(const nlohmann::json& data);
}  // namespace fio::internal