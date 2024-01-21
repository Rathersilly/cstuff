#include "mygui.h"
#include "common.h"
#include "imgui.h"
#include <string>
#include <string_view>

void MyGuiElement::go() {
  if (!active)
    return;
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
  ImGui::Begin(name_, &active);
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

void SimpleTestWindow::go() {
  // 2. Show a simple window that we create ourselves. We use a Begin/End pair
  // to create a named window.
  {
    ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!"
                                   // and append into it.

    ImGui::Text("This is some useful text."); // Display some text (you can
                                              // use a format strings too)
    /* ImGui::Checkbox( */
    /*     "Demo Window", */
    /*     &show_demo_window); // Edit bools storing our window open/close
     * state */
    ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &f, 0.0f,
                       1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3(
        "clear color",
        (float *)&clear_color); // Edit 3 floats representing a color

    if (ImGui::Button("Button")) // Buttons return true when clicked (most
                                 // widgets return true when edited/activated)
      counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    /* ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", */
    /*             1000.0f / io.Framerate, io.Framerate); */
    ImGui::End();
  }
  /* mygui(); */

  // 3. Show another simple window.
  if (show_another_window) {
    ImGui::Begin(
        "Another Window",
        &show_another_window); // Pass a pointer to our bool variable (the
                               // window will have a closing button that will
                               // clear the bool when clicked)
    ImGui::Text("Hello from another window!");
    guio = ImGui::GetIO(); // update this to get current framerate.
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / guio.Framerate, guio.Framerate);

    /* std::cout << elapsed.count() << std::endl; */
    if (ImGui::Button("Close Me"))
      show_another_window = false;
    ImGui::End();
  }
}
