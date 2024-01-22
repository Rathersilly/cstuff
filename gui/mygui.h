#ifndef MYGUI_H
#define MYGUI_H

#include "common.h"
void mygui();

struct GuiControlElement : public GuiElement {

  GuiControlElement(const char *n = "Unnamed GuiControlElement")
      : GuiElement{n} {}

  void go() override;
};
struct MyGuiElement : public GuiElement {

  void go() override;
  MyGuiElement(const char *n = "Unnamed MyGuiElement") : GuiElement{n} {}
};

struct SimpleTestWindow : public GuiElement {

  inline static float f = 0.0f;
  inline static int counter = 0;
  inline static bool show_another_window = true;
  inline static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  // unnecessary?
  SimpleTestWindow(const char *n = "Unnamed SimpleTestWindow")
      : GuiElement{n} {}

  void go() override;
};
#endif // !MYGUI_H
