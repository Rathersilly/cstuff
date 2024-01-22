#ifndef COMMON_H
#define COMMON_H

#include <SDL.h>
#include <SDL_opengl.h>

#include <chrono> // steady_clock
#include <functional>
#include <iostream>
#include <stdio.h>
#include <string>
#include <string_view>
#include <vector>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"

using std::string_view;
using namespace std::literals;
using namespace std::chrono_literals;

// SDL and OpenGL handles
extern SDL_Window *screen;
extern SDL_GLContext gl_context;
extern const char *glsl_version;

// ImGui handles
extern ImGuiIO guio;

static int kTarget_framerate = 60;
static std::chrono::milliseconds kTarget_frame_duration(1000ms /
                                                        kTarget_framerate);

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
  const char *name;
  bool active = true;
  void activate() { active = true; }
  void deactivate() { active = false; }
  void toggle() { active == true ? active = false : active = true; }

  /* virtual const char *name(); */
  virtual void go() {
    std::cout << "GuiElement virtual void go()" << std::endl;
  }
  GuiElement(const char *n = "Unnamed Gui Element") : name{n} {}
  /* virtual GuiElement() {} */
};

// for calling ImGui functions like ShowDemoWindow, but being able to store
// them in the same array as GuiElements you create
struct GuiFunction : public GuiElement {

  std::function<void(bool)> go_function;
  void go() override { go_function(active); }

  GuiFunction(std::function<void(bool)> fun,
              const char *n = "Unnamed GuiFunction")
      : GuiElement(n), go_function{fun} {}
};

struct MyElement;
struct GuiFunction;

struct AppState {
  // TODO should these be unique_ptrs?
  std::vector<GuiElement *> GuiState;
};
extern AppState State;

#endif // !COMMON_H
