#include "Simple_window.h"// get access to our window library
#include "Graph.h"// get access to our graphics library facilities
using namespace Graph_lib;// our graphics facilities are in Graph_lib

// ch 14 ex: smiley and frowney faces

struct Smiley : Circle {
	Smiley(Point p, int rr) // center and radius
	: Circle(p, rr) {
		leye = new Mark(Point{p.x-r/2,p.y - r/2}, 'O');
		reye = new Mark(Point{p.x+r/2,p.y - r/2}, 'O');
	}

	void draw_lines() const  {
		Circle::draw_lines();
		if (fill_color().visibility()) {	// fill
			fl_color(fill_color().as_int());
			fl_pie(point(0).x,point(0).y,r+r-1,r+r-1,0,360);
			fl_color(color().as_int());	// reset color
		}
		fl_arc(point(0).x + r/2,point(0).y+ r/2,r,r,225,315);

		leye->draw_lines();
		reye->draw_lines();
	}

	Mark *leye;
	Mark *reye;
};
struct Frowney : Circle {
	Frowney(Point p, int rr) // center and radius
	: Circle(p, rr) { }

	void draw_lines() const  {
		Circle::draw_lines();
		if (fill_color().visibility()) {	// fill
			fl_color(fill_color().as_int());
			fl_pie(point(0).x,point(0).y,r+r-1,r+r-1,0,360);
			fl_color(color().as_int());	// reset color
		}
		cout << point(0).x << ", " << point(0).y << endl;
		fl_arc(point(0).x + r/2,point(0).y+ r,r,r,45,135);

		Mark(Point(center().x-r/2,center().y - r/2), 'O').draw_lines();
		Mark(Point(center().x+r/2,center().y - r/2), 'O').draw_lines();
	}
};



int main()
{

	Point pt {100,100};

	Simple_window win {pt,600,400,"Canvas"};// make a simple window
	Smiley s(Point{175,200},100);
	Frowney f(Point{425,200},100);


win.attach(s);
win.attach(f);

win.wait_for_button();// ghve control to the display engine


}
