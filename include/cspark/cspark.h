#pragma once

#include <string>
#include <vector>

namespace cspark {
const std::vector<std::string> lang_entries = {"C", "C++"};
const std::vector<std::string> type_entries = {"executable", "library"};
const std::vector<std::string> c_entries = {"89", "99", "11", "17", "23"};
const std::vector<std::string> cpp_entries = {"98", "11", "14", "17", "20", "23"};

enum class Screen {
  SETUP,
  SUCCESS,
  FAIL
};

bool createProject(const std::string &path, const std::string &project_name, int language, int std, int type);
} // namespace cspark
