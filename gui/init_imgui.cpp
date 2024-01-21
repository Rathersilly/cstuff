#include "init_imgui.h"
#include "init_imgui_style.h"
#include <iostream>

// get the current IO state with:
// guio = ImGui::GetIO();
// must update it to get current state (ie to get current framerate
ImGuiIO guio;

void init_imgui() {

  IMGUI_CHECKVERSION();
  // This sets the imgui global variable ImGuiContext *GImGui
  ImGui::CreateContext();
  guio = ImGui::GetIO();

  // https://stackoverflow.com/questions/34288844/what-does-casting-to-void-really-do
  // casting to void apparently is to suppress compiler warnings
  (void)guio;
  guio.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  guio.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
                                         //
  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForOpenGL(screen, gl_context);
  ImGui_ImplOpenGL3_Init(glsl_version);
  // from gpt
  SDL_GL_SetSwapInterval(0); // Disable vsync
  /* return ImGui::GetIO(); */
  init_imgui_style();
}
// maybe move the sample windows here
void imgui_simple_window() {}

void init_imgui_style() {
  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  imgui_cherry_style();
}
