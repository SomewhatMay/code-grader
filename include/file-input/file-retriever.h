#pragma once

#include <string>
#include <vector>

namespace fio {
/**
 * Return a vector of `question_id`s based on the names
 * of each question in the resources/questions folder.
 */
std::vector<std::string> get_question_list();
}  // namespace fio