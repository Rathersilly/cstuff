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
#include <chrono> // imtrying to get framerate
#include <iostream>
using std::cout;
using std::endl;

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

AppState State;
#include <iostream>
// Main code
int main(int, char **) {
  // sometimes get "Invalid operands to binary expression
  // ('ostream' (aka 'int') and 'const char[]')
  // when putting couts in a different cpp file
  init_window();
  init_imgui();

  // ImGui state
  GuiFunction foo([](bool) { ImGui::ShowDemoWindow(); });
  State.GuiState.push_back(&foo);
  MyGuiElement bar;
  SimpleTestWindow baz;
  State.GuiState.push_back(&bar);
  State.GuiState.push_back(&baz);
  /* State.GuiState.push_back(&ImGui::ShowDemoWindow); */
  /* State.GuiState.push_back(GuiFunction([](bool) { ImGui::ShowDemoWindow();
   * })); */
  /* State.GuiState.push_back(MyGuiElement{}); */
  bool show_demo_window = true;
  /* show_demo_window = false; */
  /* show_demo_window = true; */
  bool show_another_window = false;
  show_another_window = true;

  // Main loop
  bool done = false;
  int frames_elapsed = 0;
  int frames_this_second = 0;
  int ticks_this_frame = 0;
  int fps = 0;
  int desired_framerate = 60;
  double desired_ticks_per_frame = 1 / desired_framerate;
  /* Uint32  */

  auto start{std::chrono::high_resolution_clock::now()};
  auto end{std::chrono::high_resolution_clock::now()};
  std::chrono::duration<double> elapsed{end - start};

  std::cout << "Elapsed time: " << elapsed.count()
            << '\n'; // C++20's chrono::duration operator<<

  // unused - not sure exactly how/whether to use this since context is not part
  // of imgui api (its implementation instead)
  // feel free to delete
  ImGuiContext *context = ImGui::GetCurrentContext();

  while (!done) {
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
    ////////////////// some random nonsense - deletable
    int i = 0;
    for (auto a : State.GuiState) {

      /* cout << i << " " << a->active << " : "; */
      a->go();
    }
    /* foo.go(); */
    /* cout << SDL_GetTicks() << " "; */

    //////////////////////

    ///////////// timing nonsense
    /* std::cout << guio.Framerate << std::endl; */
    /* std::cout << frame_count << std::endl; */

    ++frames_elapsed;
    ++frames_this_second;
    ++ticks_this_frame;
    /* std::cout << GREEN << frames_elapsed << RESET << std::endl; */

    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    // SDL_TICKS_PASSED(A, B)
    // /* if you want to wait 100 ms, you could do this: */
    // Uint32 timeout = SDL_GetTicks() + 100;
    // while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
    /* ... do work until timeout has elapsed */
    if (ticks_this_frame >= desired_ticks_per_frame) {

      std::cout << GREEN << "Updating: " << frames_this_second << endl;
      std::cout << YELLOW << "frames_this_second: " << frames_this_second
                << RESET << std::endl;
      frames_this_second = 0;
      ticks_this_frame = 0;
      start = std::chrono::high_resolution_clock::now();
      /* std::cout << elapsed.count() << std::endl; */
      /* std::cout << tickspersec << std::endl; */
      /* std::cout << GREEN << guio.DeltaTime << RESET << std::endl; */
      /* std::cout << BLUE << guio.Framerate << RESET << std::endl; */
    }

    present_scene();
  }

  cleanup();

  return 0;
}
