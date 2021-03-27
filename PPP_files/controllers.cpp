#include "Simple_window.h"// get access to our window library
#include "Graph.h"// get access to our graphics library facilities
using namespace Graph_lib;// our graphics facilities are in Graph_lib

// ch 14 ex 16 - controllers

struct Controller {
	Controller(Shape& s, int lev = 0) : shape(&s), level(lev) {
		if (level == 0) {
			state = false;
		}
		else {
			state = true;
		}
		color = shape->color().as_int();
	}


	// wait this is a struct
	//protected:
	virtual void on() {};
	virtual void off() {};
	virtual void set_level(int i) {};
	virtual void show() {};

	Shape* shape;
	bool state;
	int level;
	//Color color;
	int color;
};
struct Test_Controller : public Controller {
	using Controller::Controller;

	void on() {
		cout << "state is now on" << endl;
		level = 1;
		state = true;
	}
	void off() {
		cout << "state is now off" << endl;
		level = 0;
		state = false;
	}
	void show() {
		cout << "state is currrently: " << state << endl;
		cout << "level is currently: " << level << endl;
	}


};
struct Color_Controller : public Controller {
	using Controller::Controller;
	void on() {
		cout << "state is now visible" << endl;
		//shape->set_color(Color::visible);
		level = 1;
		state = true;
	}
	void off() {
		cout << "state is now invisible" << endl;
		//shape->set_color(Color::invisible);

		level = 0;
		state = false;
	}
	void next() {
		if (color == Color::black) {
			color = Color::red;
			cout << "should be red" << endl;
		}
		else {
			color = Color::black;
		}
		shape->set_color(color);
	}
	void show() {
		//cout << "color is currrently: " << color.as_int() << endl;
		cout << "color is currrently: " << color << endl;
		//cout << "visibility is currently: " << level << endl;
	}
};

int main()
{

	Point pt {100,100};

	Simple_window win {pt,600,400,"Canvas"};// make a simple window

	Line l({100,100},{200,200});
	l.set_style(Line_style(Line_style::solid, 4));
	l.set_color(Color::black);


	Color_Controller c(l);
	c.on();
	c.show();
	//c.off();
	c.next();
	c.next();
	c.show();

	win.attach(l);

	win.wait_for_button();// ghve control to the display engine


}
