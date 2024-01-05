#include "draw.h"
#include <iostream>

extern ImVec4 clear_color;

void present_scene() {
  // geting weird (incorrect) "Invalid operands to binary expression
  // ('ostream' (aka 'int') and 'const char[]')
  // but program works as expected
  //
  std::cout << "hi from draw.cpp" << std::endl;
  // Rendering
  ImGui::Render();
  glViewport(0, 0, (int)app.igio.DisplaySize.x, (int)app.igio.DisplaySize.y);
  glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
               clear_color.z * clear_color.w, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  SDL_GL_SwapWindow(app.win);
}
