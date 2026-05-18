#include <filesystem>
#include <format>
#include <fstream>
#include <print>
#include <string>

int main(int argc, char **argv) {
  std::string name = argv[1];

  if (name == "--help") {
    std::println("use this vector of aguments:\n");
    std::println("<name> <type> <lang> <std> <path>\n");
    std::println("name: project name");
    std::println("type: exe or lib");
    std::println("lang: c or c++");
    std::println("std: version of lang (eg. 23 for C++23)");
    std::println("path: path where project will be created");
    return 0;
  }

  std::string type = argv[2];
  std::string lang = argv[3];
  std::string std = argv[4];
  std::string path = argv[5];

  if (type != "exe" && type != "lib" || lang != "c" && lang != "c++") {
    std::println("invalid arguments");
    return -1;
  }

  path = path + "/" + name;

  std::string extension;

  if (type == "exe") {
    type = "executable";
  }
  if (type == "lib") {
    type = "library";
  }
  if (lang == "c") {
    extension = "c";
    lang = "C";
  }
  if (lang == "c") {
    extension = "cpp";
    lang = "CXX";
  }
  if (type == "exe") {
    type = "executable";
  }
  if (type == "lib") {
    type = "library";
  }

  std::println("creating directory {}...", path);
  std::filesystem::create_directory(path);
  std::println("creating directory {}...", path + "/include");
  std::filesystem::create_directory(path + "/include");
  std::println("creating directory {}...", path + "/lib");
  std::filesystem::create_directory(path + "/lib");
  std::println("creating directory {}...", path + "/src");
  std::filesystem::create_directory(path + "/src");
  std::println("creating directory {}...", path + "/build");
  std::filesystem::create_directory(path + "/build");

  std::println("generating CmakeLists.txt file...");
  std::ofstream file(path + "/CMakeLists.txt");
  file << std::format(R"(cmake_minimum_required(VERSION 4.2.0)
project({})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_{}_STANDARD {})

add_{}(${{PROJECT_NAME}}
  src/main.{}
)

set_target_properties(${{PROJECT_NAME}} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${{CMAKE_BINARY_DIR}}/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${{CMAKE_BINARY_DIR}}/Release
)

target_include_directories(${{PROJECT_NAME}} PRIVATE include)
target_link_directories(${{PROJECT_NAME}} PRIVATE lib)

target_link_libraries(${{PROJECT_NAME}} PRIVATE #libs to link))",
                      name, type, lang, std, extension);
  file.close();

  std::println("generating .clang-format file...");
  file.open(path + "/.clang-format");
  file << R"(BasedOnStyle: LLVM
IndentWidth: 2
ColumnLimit: 200
AllowShortFunctionsOnASingleLine: Empty
AllowShortEnumsOnASingleLine: false
)";

  file.close();

  file.open(path + "/src/main." + extension);

  if (extension == "c" && type == "executable") {
    file << R"(#include <stdio.h>

int main() {
  printf("Hello World!\n");
  return 0;
}
    )";
  }

  if (extension == "cpp" && type == "executable") {
    file << R"(#include <iostream>

int main() {
  std::cout << "Hello World!\n";
  return 0;
}
    )";
  }

  std::println("\nDone!");
  return 0;
}
