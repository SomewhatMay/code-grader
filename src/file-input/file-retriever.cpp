#include "file-input/file-retriever.h"

#include <filesystem>

#include "globals.h"

namespace fs = std::filesystem;

std::vector<std::string> get_question_list() {
  // Change this line to use an absolute or relative path as needed
  std::vector<std::string> question_list;
  fs::directory_iterator iterator(globals::QUESTIONS_PATH);

  for (const auto& entry : iterator) {
    if (entry.is_directory()) {
      std::string question_id = entry.path().filename().string();
      question_list.push_back(question_id);
    }
  }

  return question_list;
}