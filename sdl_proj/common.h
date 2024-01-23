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

using std::string_view;
using namespace std::literals;
using namespace std::chrono_literals;

// SDL and OpenGL handles
extern SDL_Window *window;
extern SDL_GLContext gl_context;
extern const char *glsl_version;

static int kTarget_framerate = 60;
static std::chrono::milliseconds kTarget_frame_duration(1000ms /
                                                        kTarget_framerate);

#endif
