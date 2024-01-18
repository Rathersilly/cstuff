/* #include "setup_imgui.h" */
#include "cleanup.h"
#include "color_macros.h"
#include "draw.h"
#include "init_imgui.h"
#include "init_imgui_style.h"
#include "init_window.h"
#include "mygui.h"
#include <chrono> // imtrying to get framerate
#include <iostream>
using std::cout;
using std::endl;

App app;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

#include <iostream>
// Main code
int main(int, char **) {
  // sometimes get "Invalid operands to binary expression
  // ('ostream' (aka 'int') and 'const char[]')
  // when putting couts in a different cpp file
  init_window();
  init_imgui();

  // ImGui state
  bool show_demo_window = true;
  show_demo_window = false;
  show_demo_window = true;
  bool show_another_window = false;
  show_another_window = true;

  // Main loop
  bool done = false;
  int ticks = 0;
  int tickspersec = 0;

  auto start{std::chrono::high_resolution_clock::now()};
  auto end{std::chrono::high_resolution_clock::now()};
  std::chrono::duration<double> elapsed{end - start};
  int frame_flag = 0;

  std::cout << elapsed.count() << '\n'; // C++20's chrono::duration operator<<
                                        //
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
          event.window.windowID == SDL_GetWindowID(app.win))
        done = true;
    }

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // need to think of where to store bools of what imgui windows to keep open
    // in this file its a local bool
    // what data structure? map? tuple?
    // app.state.imgui
    // app.state.sdl etc
    //
    // 1. Show the big demo window (Most of the sample code is in
    // ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear
    // ImGui!).
    if (show_demo_window)
      ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair
    // to create a named window.
    {
      static float f = 0.0f;
      static int counter = 0;

      ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!"
                                     // and append into it.

      ImGui::Text("This is some useful text."); // Display some text (you can
                                                // use a format strings too)
      ImGui::Checkbox(
          "Demo Window",
          &show_demo_window); // Edit bools storing our window open/close state
      ImGui::Checkbox("Another Window", &show_another_window);

      ImGui::SliderFloat("float", &f, 0.0f,
                         1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
      ImGui::ColorEdit3(
          "clear color",
          (float *)&clear_color); // Edit 3 floats representing a color

      if (ImGui::Button("Button")) // Buttons return true when clicked (most
                                   // widgets return true when edited/activated)
        counter++;
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      /* ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", */
      /*             1000.0f / io.Framerate, io.Framerate); */
      ImGui::End();
    }
    mygui();

    // 3. Show another simple window.
    if (show_another_window) {
      ImGui::Begin(
          "Another Window",
          &show_another_window); // Pass a pointer to our bool variable (the
                                 // window will have a closing button that will
                                 // clear the bool when clicked)
      ImGui::Text("Hello from another window!");
      ++ticks;
      ++tickspersec;
      /* std::cout << app.igio.Framerate << std::endl; */
      /* std::cout << frame_count << std::endl; */

      end = std::chrono::high_resolution_clock::now();
      elapsed = end - start;
      if (elapsed.count() > 1) {
        start = std::chrono::high_resolution_clock::now();
        std::cout << elapsed.count() << std::endl;
        std::cout << tickspersec << std::endl;
        tickspersec = 0;
        std::cout << GREEN << app.igio.DeltaTime << RESET << std::endl;
        std::cout << BLUE << app.igio.Framerate << RESET << std::endl;
        // std::cout << ImGui::GImGui << std::endl; gimgui doesnt exist here
      }
      // bonj - this says 0 fps whats up - i copied it from example file
      // ImGui::Text takes variadic args - used to format string it seems
      // where does it update?
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                  1000.0f / app.igio.Framerate, app.igio.Framerate);

      /* std::cout << elapsed.count() << std::endl; */
      if (ImGui::Button("Close Me"))
        show_another_window = false;
      ImGui::End();
    }

    present_scene();
  }

  cleanup();

  return 0;
}