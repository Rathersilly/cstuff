/* #include "setup_imgui.h" */
#include "SDL_timer.h"
#include "cleanup.h"
#include "color_macros.h"
#include "common.h"
#include "draw.h"
#include "framerate.h"
#include "imgui/imgui.h"
#include "init_imgui.h"
#include "init_imgui_style.h"
#include "init_window.h"
#include "mygui.h"
// using namespace std::chrono_literals;

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

AppState State;

int main(int, char **) {
  init_window();
  init_imgui();

  // ImGui state

  // TODO make this able to toggle active - make lambda HOF first
  // also can combine these 2 lines somehow with emplace_back()
  GuiFunction foo([](bool) { ImGui::ShowDemoWindow(); }, "DemoWindow");
  State.GuiState.push_back(&foo);
  MyGuiElement bar("This Window!");
  SimpleTestWindow baz;
  State.GuiState.push_back(&bar);
  State.GuiState.push_back(&baz);

  GuiControlElement gui_controller;
  bool show_metrics = true;

  // Main loop
  bool done = false;

  while (!done) {
    auto start_time = std::chrono::steady_clock::now();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT)
        done = true;
      if (event.type == SDL_WINDOWEVENT &&
          event.window.event == SDL_WINDOWEVENT_CLOSE &&
          event.window.windowID == SDL_GetWindowID(screen))
        done = true;
    }

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowMetricsWindow(&show_metrics);

    // show active Gui Elements
    for (auto a : State.GuiState) {
      a->go();
    }
    gui_controller.go();

    present_scene();

    cap_framerate(start_time);
  }

  cleanup();

  return 0;
}
