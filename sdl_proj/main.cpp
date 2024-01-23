#include "SDL_timer.h"
#include "cleanup.h"
#include "color_macros.h"
#include "common.h"
#include "draw.h"
#include "framerate.h"
#include "init_window.h"
// using namespace std::chrono_literals;

int main(int, char **) {
  init_window();

  // Main loop
  bool done = false;

  while (!done) {
    auto start_time = std::chrono::steady_clock::now();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        done = true;
      if (event.type == SDL_WINDOWEVENT &&
          event.window.event == SDL_WINDOWEVENT_CLOSE &&
          event.window.windowID == SDL_GetWindowID(window))
        done = true;
    }

    present_scene();

    cap_framerate(start_time);
  }

  cleanup();

  return 0;
}
