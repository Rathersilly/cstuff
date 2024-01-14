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
void mygui() {
  bool showx = true;
  ImGui::PushItemWidth(ImGui::GetFontSize() * -12);
  ImGui::Begin("MY WINDOW", &showx);
  ImGui::Text("HIIIIIIIIIIIIIIIII");
  ImGui::End();
}
