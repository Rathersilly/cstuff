#include "mygui.h"
void mygui() {
  bool showx = true;
  const ImGuiViewport *main_viewport = ImGui::GetMainViewport();

  // ImGuiCond is a predicate to determine when to call this function
  // eg ImGuiCond_FirstUseEver will only change the Pos once, and
  // even then only if it is not set in imgui.ini
  ImGui::SetNextWindowPos(
      ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20),
      ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(50, 80), ImGuiCond_Always);
  ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

  ImGui::Begin("MY WINDOW", &showx);

  ImGui::Text("HIIIIIIIIIIIIIIIII");
  ImGui::End();
}
