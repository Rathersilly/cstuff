#include <functional>
#include <iostream>
#include <vector>

struct GuiElement {
  bool active = true;

  virtual void go() {
    /* std::cout << "GuiElement virtual void go()" << std::endl; */
  }
};

// for calling ImGui functions like ShowDemoWindow
struct GuiFunction : public GuiElement {
  const char *name_ = "GuiFunction";

  std::function<void(bool)> go_function;

  void go() override { go_function(active); }

  GuiFunction(std::function<void(bool)> fun) : go_function{fun} {}
};

struct AppState {
  std::vector<GuiElement> GuiState;
};

AppState State;

int main(int argc, char *argv[]) {

  GuiFunction foo([](bool) { ImGui::ShowDemoWindow(); });
  State.GuiState.push_back(foo);
  // simplified, abstract version of the main loop
  while (true) {
    for (auto &a : State.GuiState) {

      a.go();
    }
    foo.go();
  }
  return 0;
}
