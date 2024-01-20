#include "mygui.h"
#include "imgui.h"
void mygui() {
  bool showx = true;
  const ImGuiViewport *main_viewport = ImGui::GetMainViewport();

  // ImGuiCond is a predicate to determine when to call this function
  // eg ImGuiCond_FirstUseEver will only change the Pos once, and
  // even then only if it is not set in imgui.ini
  ImGui::SetNextWindowPos(
      ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20),
      ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(500, 800), ImGuiCond_Always);
  ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

  static int vector_max_size = 0;
  ImGui::Begin("MY WINDOW", &showx);
  ImGui::TextWrapped("This is some useful text."); // Display some text (you can
  ImGui::TextWrapped(
      "This Elements in Vectoraaaafd fd fds fds aaaaaaaaaaa dsfsadfsdfds fis "
      "some useful text."); // Display some text (you can
  ImGui::SliderInt("Elements in Vector", &vector_max_size, 0, 100);
  ImGui::Text("Unsorted Vector:"); // Display some text (you can
  ImGui::Text("Sorted Vector:");   // Display some text (you can
  double some_num = 123.456;
  int some_num2 = 789;
  ImGui::Text("Some numbers: %2.2f %3i", some_num, vector_max_size);

  ImGui::Checkbox("Demo Window", &showx);

  ImGui::Text("HIIIIIIIIIIIIIIIII");
  ImGui::End();
}
