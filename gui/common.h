#ifndef COMMON_H
#define COMMON_H

#include <SDL.h>
#include <SDL_opengl.h>
#include <functional>
#include <iostream>
#include <stdio.h>
#include <vector>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"

// SDL and OpenGL handles
extern SDL_Window *screen;
extern SDL_GLContext gl_context;
extern const char *glsl_version;

// ImGui handles
extern ImGuiIO guio;

// State.GuiState is a vector of GuiElements
// A GuiElement contains what ImGui refers to as a ImGuiWindow,
// as well as a bool containing its on/off state
//
// ImGuiContext has something similar, but I think it makes sense
// to have a struct with both the state and a function pointer to the actual
// {begin (code) end } that makes up an imgui window
//
// in imgui_iternal.h:
// struct ImGuiContext contains ImVector<ImGuiWindow*>  Windows

// base class for gui elements you create. begin...end goes in the go() function
struct GuiElement {
  bool active = true;
  void activate() { active = true; }
  void deactivate() { active = false; }
  void toggle() { active == true ? active = false : active = true; }

  /* virtual const char *name(); */
  virtual void go() {
    std::cout << "GuiElement virtual void go()" << std::endl;
  }
  /* virtual GuiElement() {} */
};

// for calling ImGui functions like ShowDemoWindow, but being able to store
// them in the same array as GuiElements you create
struct GuiFunction : public GuiElement {
  const char *name_ = "GuiFunction";
  /* const char *name() override { return name_; }; */
  std::function<void(bool)> go_function;

  void go() override { go_function(active); }

  GuiFunction(std::function<void(bool)> fun) : go_function{fun} {}
};

struct MyElement;
struct GuiFunction;

struct AppState {
  /* std::vector<GuiElement> GuiState; */
  std::vector<GuiElement *> GuiState;
  /* std::vector<std::reference_wrapper<GuiFunction>> GuiState; */
  /* std::vector<GuiFunction> GuiState; */
  // vector of gui structs?
  //
};
extern AppState State;

#endif // !COMMON_H
