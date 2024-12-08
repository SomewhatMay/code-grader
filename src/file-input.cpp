#include "file-input.h"

#include <filesystem>

#include "globals.h"

using std::vector, std::string;
namespace fs = std::filesystem;

vector<string> get_question_list() {
  // Change this line to use an absolute or relative path as needed
  vector<string> question_list;
  fs::directory_iterator iterator(globals::QUESTIONS_PATH);

  for (const auto &entry : iterator) {
    if (entry.is_directory()) {
      string question_id = entry.path().filename().string();
      question_list.push_back(question_id);
    }
  }

  return question_list;
}