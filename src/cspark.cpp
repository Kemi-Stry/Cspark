#include <filesystem>
#include <fstream>
#include <string>

#include <cspark/cspark.h>

bool cspark::createProject(const std::string &path, const std::string &project_name, int language, int std, int type) {
  bool success;
  std::string lang = (language == 0) ? "C" : "CXX";
  std::string file_extension = (language == 0) ? ".c" : ".cpp";
  std::string standard = (language == 0) ? c_entries.at(std) : cpp_entries.at(std);
  std::string project_type = type_entries.at(type);

  success = std::filesystem::create_directories(path + "/" + project_name);
  success = std::filesystem::create_directory(path + "/" + project_name + "/include");
  success = std::filesystem::create_directory(path + "/" + project_name + "/lib");
  success = std::filesystem::create_directory(path + "/" + project_name + "/src");
  success = std::filesystem::create_directory(path + "/" + project_name + "/build");

  std::ofstream file(std::filesystem::path(path + "/" + project_name + "/CMakeLists.txt"));
  if (!file.good()) {
    return false;
  }

  file << std::format(R"(cmake_minimum_required(VERSION 4.2.0)
project({})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_{}_STANDARD {})

add_{}(${{PROJECT_NAME}}
  src/main{}
)

set_target_properties(${{PROJECT_NAME}} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${{CMAKE_BINARY_DIR}}/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${{CMAKE_BINARY_DIR}}/release
)

target_include_directories(${{PROJECT_NAME}} PRIVATE include)
target_link_directories(${{PROJECT_NAME}} PRIVATE lib)

# target_link_libraries(${{PROJECT_NAME}} PRIVATE #libs to link))",
                      project_name, lang, standard, project_type, file_extension);
  file.close();
  file.open(std::filesystem::path(path + "/" + project_name + "/.clang-format"));
  if (!file.good()) {
    return false;
  }
  file << R"(BasedOnStyle: LLVM
IndentWidth: 2
ColumnLimit: 200
AllowShortFunctionsOnASingleLine: Empty
AllowShortEnumsOnASingleLine: false)";
  file.close();

  if (project_type == "executable") {
    if (lang == "C") {
      file.open(std::filesystem::path(path + "/" + project_name + "/src/main.c"));
      if (!file.good()) {
        return false;
      }
      file << R"(#include <stdio.h>

int main() {
  printf("Hello, World!\n");
  return 0;
}
      )";
      file.close();
    }
    if (lang == "CXX") {
      file.open(std::filesystem::path(path + "/" + project_name + "/src/main.cpp"));
      if (!file.good()) {
        return false;
      }
      file << R"(#include <iostream>

int main() {
  std::cout << "Hello, World!\n";
  return 0;
}
      )";

      file.close();
    }
  }
  return success;
}
