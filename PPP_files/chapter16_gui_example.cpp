//#include "Simple_window.h"// get access to our window library
//#include "Graph.h"// get access to our graphics library facilities
#include "GUI.h"
using namespace Graph_lib;// our graphics facilities are in Graph_lib

// ch 16.5 - 16.7 gui example

struct Lines_window : Graph_lib::Window {
	Lines_window(Point xy,int w,int h, const string& title);
	Open_polyline lines;
	Menu color_menu;
	Button menu_button;

	static void cb_red(Address,Address a) {reference_to<Lines_window>(a).red_pressed(); }
	static void cb_blue(Address,Address a) {reference_to<Lines_window>(a).blue_pressed(); }
	static void cb_black(Address,Address a) {reference_to<Lines_window>(a).black_pressed(); }
	static void cb_menu(Address,Address a) {reference_to<Lines_window>(a).menu_pressed(); }
	void red_pressed(){change(Color::red); hide_menu();}
	void blue_pressed(){change(Color::blue); hide_menu();}
	void black_pressed(){change(Color::black); hide_menu();}
	void menu_pressed(){menu_button.hide();color_menu.show();}

	void change(Color c) {lines.set_color(c); }

	void hide_menu() { color_menu.hide();menu_button.show();}
private:
	Button next_button;
	Button quit_button;
	In_box next_x;
	In_box next_y;
	Out_box xy_out;

	void next();
	void quit();
};
Lines_window::Lines_window(Point xy,int w,int h,const string& title)
	: Window{xy,w,h,title},
	next_button{Point{x_max()-150,0},70,20,"Next point",
		[](Address, Address pw) {reference_to<Lines_window>(pw).next();}},
	quit_button{Point{x_max()-70,0},70,20,"Quit",
		[](Address, Address pw) {reference_to<Lines_window>(pw).quit();}},
	next_x{Point{x_max() - 310,0},50,20,"next x:"},
	next_y{Point{x_max() - 210,0},50,20,"next y:"},
	xy_out{Point{100,0},100,20,"current (x,y):"},
	color_menu{Point{x_max()-74,40},70,20,Menu::vertical,"color"},
	menu_button{Point{x_max()-80,30},80,20,"color menu",cb_menu}
{
	attach(next_button);
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(xy_out);
	xy_out.put("no point");
	attach(lines);
	color_menu.attach(new Button{Point{0,0},0,0,"red",cb_red});
	color_menu.attach(new Button{Point{0,0},0,0,"blue",cb_blue});
	color_menu.attach(new Button{Point{0,0},0,0,"black",cb_black});
	attach(color_menu);
	color_menu.hide();
	attach(menu_button);
}
void Lines_window::quit() {
	hide();
}
void Lines_window::next() {
	int x = next_x.get_int();
	int y = next_y.get_int();
	lines.add(Point{x,y});
	ostringstream ss;
	ss << '(' <<x<<','<<y<<')';
	xy_out.put(ss.str());

	redraw();
}

int main()
{
	Point pt {100,100};
	//Window win(pt, 600,400,"Hey there");
	try {
		Lines_window win{Point{100,100},600,400,"lines"};
		return gui_main();
	}
	catch(exception& e) {
		cerr << "exception: " <<e.what()<<endl;
		return 1;
	}
	catch(...) {
		cerr << "some exception" << endl;
		return 2;
	}
}
