#include <functional>
#include <iostream>
#include <vector>
using namespace std;

struct GuiElement {
  bool active = true;
  void activate() { active = true; }
  void deactivate() { active = false; }
  void toggle() { active == true ? active = false : active = true; }

  virtual void go() {}
  virtual ~GuiElement() {}
};

// for calling ImGui functions like ShowDemoWindow
struct GuiFunction : public GuiElement {
  std::function<void(bool)> go_function;

  void go() override { go_function(active); }

  GuiFunction(std::function<void(bool)> fun) : go_function{fun} {}
};

void demo(bool arg = true) { cout << "demo" << endl; }
int main(int argc, char *argv[]) {

  GuiFunction foo([](bool) { demo(); });
  foo.go();
  return 0;
}
