#include "common.h"

extern std::chrono::milliseconds kTarget_frame_duration;

void cap_framerate(std::chrono::steady_clock::time_point);

// move this to cpp if needed
void cap_framerate(std::chrono::steady_clock::time_point start_time) {
  auto end_time = std::chrono::steady_clock::now();
  auto frame_duration = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - start_time);

  auto sleep_duration = kTarget_frame_duration - frame_duration;

  if (sleep_duration > std::chrono::milliseconds(0)) {
    SDL_Delay(sleep_duration.count());
  }
}
