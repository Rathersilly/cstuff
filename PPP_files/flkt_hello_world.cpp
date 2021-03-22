#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Round_Button.H>

int main(int argc, char **argv) {
  Fl_Window *window = new Fl_Window(340,180);
  Fl_Box *box = new Fl_Box(20,40,300,100,"Hello, World!");
  box->box(FL_UP_BOX);
  box->labelfont(FL_BOLD+FL_ITALIC);
  box->labelsize(36);
  box->labeltype(FL_SHADOW_LABEL);

  int x = 5; int y = 5;
  int width =  40; int height = 20;

	Fl_Button *button = new Fl_Button(x, y, width, height, "label");
	//Fl_Light_Button *lbutton = new Fl_Light_Button(x, y, width, height);
	//Fl_Round_Button *rbutton = new Fl_Round_Button(x, y, width, height, "label");
	button->type(FL_NORMAL_BUTTON);
//lbutton->type(FL_TOGGLE_BUTTON);
//rbutton->type(FL_RADIO_BUTTON);
  
  window->end();
  window->show(argc, argv);
  return Fl::run();
} 
