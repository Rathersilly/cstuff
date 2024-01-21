/* #include "setup_imgui.h" */
#include "SDL_timer.h"
#include "cleanup.h"
#include "color_macros.h"
#include "common.h"
#include "draw.h"
#include "imgui/imgui.h"
#include "init_imgui.h"
#include "init_imgui_style.h"
#include "init_window.h"
#include "mygui.h"
#include <chrono> // steady_clock
#include <iostream>
using std::chrono::steady_clock;

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

AppState State;
void cap_framerate();
#include <iostream>

int main(int, char **) {
  init_window();
  init_imgui();

  // ImGui state
  // TODO create a gui element that manages the others
  // have it create a label and checkbox for each one
  // can combine these 2 lines somehow with emplace_back()

  GuiFunction foo([](bool) { ImGui::ShowDemoWindow(); });
  State.GuiState.push_back(&foo);
  MyGuiElement bar;
  SimpleTestWindow baz;
  State.GuiState.push_back(&bar);
  State.GuiState.push_back(&baz);

  // Main loop
  bool done = false;

  int target_framerate = 60;
  std::chrono::milliseconds target_frame_duration(1000 / target_framerate);

  // unused - not sure exactly how/whether to use this since context is not part
  // of imgui api (its implementation instead)
  // feel free to delete
  ImGuiContext *context = ImGui::GetCurrentContext();

  while (!done) {
    auto start_time = std::chrono::steady_clock::now();
    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to
    // tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to
    // your main application, or clear/overwrite your copy of the mouse data.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input
    // data to your main application, or clear/overwrite your copy of the
    // keyboard data. Generally you may always pass all inputs to dear imgui,
    // and hide them from your application based on those two flags.
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

    bool metrics = true;
    ImGui::ShowMetricsWindow(&metrics);
    // show active Gui Elements
    for (auto a : State.GuiState) {

      a->go();
    }

    present_scene();
    //
    // TODO move this to function
    auto end_time = std::chrono::steady_clock::now();
    auto frame_duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);

    auto sleep_duration = target_frame_duration - frame_duration;

    if (sleep_duration > std::chrono::milliseconds(0)) {
      SDL_Delay(sleep_duration.count());
    }
  }

  cleanup();

  return 0;
}
