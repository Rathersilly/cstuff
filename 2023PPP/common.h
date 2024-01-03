#ifndef COMMON_H
#define COMMON_H

#include <SDL.h>
#include <stdio.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"
struct App {
  SDL_Window *win;
  // from https://www.khronos.org/opengl/wiki/OpenGL_Context
  // An OpenGL context represents many things. A context stores all of the state
  // associated with this instance of OpenGL. It represents the (potentially
  // visible) default framebuffer that rendering commands will draw to when not
  // drawing to a framebuffer object. Think of a context as an object that holds
  // all of OpenGL; when a context is destroyed, OpenGL is destroyed.

  /* ImGuiIO &temp_imgui_io; */
  SDL_GLContext gl_context;
  const char *glsl_version;
};
extern App app;
#endif // !COMMON_H
