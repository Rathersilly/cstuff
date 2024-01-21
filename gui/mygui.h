#ifndef MYGUI_H
#define MYGUI_H

#include "common.h"
void mygui();

struct MyGuiElement : public GuiElement {

  const char *name_;

  MyGuiElement() : name_{"MyGuiElement"} {}
  MyGuiElement(char *name) : name_{name} {}

  void go() override;
};
struct SimpleTestWindow : public GuiElement {

  inline static float f = 0.0f;
  inline static int counter = 0;
  inline static bool show_another_window = true;
  inline static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  const char *name_;
  SimpleTestWindow() : name_{"SimpleTestWindow"} {}

  void go() override;
};
#endif // !MYGUI_H
