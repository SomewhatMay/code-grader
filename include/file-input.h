#pragma once

#include <string>
#include <vector>

/**
 * Return a vector of names based on the folders in resources/questions.
 */
std::vector<std::string> get_question_list();

// Questions are identified through their name:
// resources/questions/<question_id>
/**
 * Return a list of all the inputs for a question as strings.
 * Each input is a separate entry in the list.
 */
std::vector<std::string> get_inputs(std::string question_id);
