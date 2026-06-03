#include <chrono>
#include <string>
#include <thread>

#include <cspark/cspark.h>
#include <ftxui/ftxui.hpp>

int main(int argc, char **argv) {
  if (argc != 2) {
    return 1;
  }

  std::string path = argv[1];
  std::string project_name = "";
  int language = 0;
  int project_type = 0;
  int std = 0;
  cspark::Screen current_screen = cspark::Screen::SETUP;

  ftxui::App screen = ftxui::ScreenInteractive::FullscreenAlternateScreen();
  ftxui::Component input = ftxui::Input(&project_name, "Project name");
  ftxui::Component lang_box = ftxui::Radiobox(&cspark::lang_entries, &language);
  ftxui::Component type_box = ftxui::Radiobox(&cspark::type_entries, &project_type);
  ftxui::Component c_box = ftxui::Radiobox(&cspark::c_entries, &std);
  ftxui::Component cpp_box = ftxui::Radiobox(&cspark::cpp_entries, &std);
  ftxui::Component create_button = ftxui::Button("Create project", [&] {
    bool success = cspark::createProject(path, project_name, language, std, project_type);
    std::thread([&] {
      std::this_thread::sleep_for(std::chrono::seconds(2));
      screen.Exit();
    }).detach();
    if (success) {
      current_screen = cspark::Screen::SUCCESS;
    } else {
      current_screen = cspark::Screen::FAIL;
    }
  });
  ftxui::Component cancel_button = ftxui::Button("exit", [&] { screen.Exit(); });

  ftxui::Component std_box = ftxui::Container::Tab({c_box, cpp_box}, &language);
  ftxui::Component container = ftxui::Container::Vertical({input, lang_box, type_box, std_box, create_button, cancel_button});

  ftxui::Component renderer = Renderer(container, [&] {
    switch (current_screen) {
    case cspark::Screen::SETUP:
      return ftxui::vbox({ftxui::text("CSpark") | ftxui::bold, ftxui::separator(), input->Render(), ftxui::separator(), ftxui::text("Language:"), lang_box->Render(), ftxui::separator(),
                          ftxui::text("Type:"), type_box->Render(), ftxui::separator(), ftxui::text(cspark::lang_entries.at(language) + " Standard:"), std_box->Render(), ftxui::separator(),
                          create_button->Render() | ftxui::color(ftxui::Color::Green), cancel_button->Render() | ftxui::color(ftxui::Color::Red)});
      break;
    case cspark::Screen::SUCCESS:
      return ftxui::text("Project Generated!") | ftxui::center | ftxui::vcenter;
      break;
    case cspark::Screen::FAIL:
      return ftxui::text("Failed");
      break;
    default:
      break;
    }
  });
  screen.Loop(renderer);
}
