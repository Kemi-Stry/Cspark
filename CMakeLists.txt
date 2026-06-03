include(FetchContent)

cmake_minimum_required(VERSION 4.2.0)
project(cspark)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

FetchContent_Declare(
ftxui
GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
GIT_TAG        main
)

FetchContent_MakeAvailable(ftxui)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/cspark.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/release
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
# target_link_directories(${PROJECT_NAME} PRIVATE lib)

target_link_libraries(${PROJECT_NAME} PRIVATE ftxui::component ftxui::dom ftxui::screen)
