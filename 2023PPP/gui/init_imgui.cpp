#include "init_imgui.h"
#include "init_imgui_style.h"
#include <iostream>

extern App app;

void init_imgui() {

  IMGUI_CHECKVERSION();
  // This sets the imgui global variable ImGuiContext *GImGui
  ImGui::CreateContext();
  app.igio = ImGui::GetIO();

  // https://stackoverflow.com/questions/34288844/what-does-casting-to-void-really-do
  // casting to void apparently is to suppress compiler warnings
  (void)app.igio;
  app.igio.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  app.igio.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
                                         //
  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForOpenGL(app.win, app.gl_context);
  ImGui_ImplOpenGL3_Init(app.glsl_version);
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
