#include "cleanup.h"

void cleanup() {
  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_GL_DeleteContext(app.gl_context);
  SDL_DestroyWindow(app.win);
  SDL_Quit();
}
