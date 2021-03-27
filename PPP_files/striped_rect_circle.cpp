#include "Simple_window.h"// get access to our window library
#include "Graph.h"// get access to our graphics library facilities
using namespace Graph_lib;// our graphics facilities are in Graph_lib

// ch 14 ex striped rectangle and circle

struct Immobile_Circle : Circle {
	Immobile_Circle (Point p, int rr) : Circle(p, rr) {}


	void move(int i, int j) { cout <<  "would move ordinarily" << endl;}

};

ostream&  operator<<(ostream& os, const Point& p) {
	return os << "x: " << p.x << ", y: " << p.y << endl;
}
struct Striped_Rectangle : Rectangle {
	Striped_Rectangle(Point xy, int ww, int hh) : Rectangle(xy, ww, hh) {}

	void draw_lines() const {
		for(auto y = point(0).y; y < point(0).y + height(); y++) {
			if (y % 4 == 0) {
				Line l(Point(point(0).x, y),Point(point(0).x + width(), y));
				l.set_style(Line_style{Line_style::solid, 2});
				l.draw_lines();
			}
			//cout << Point(point(0).x, y);
			//cout << Point(point(0).x + width(), y);
		}
		Line(Point(20,10),Point(200,10)).draw_lines();

		if (color().visibility()) {	// edge on top of fill
			fl_color(color().as_int());
			fl_rect(point(0).x,point(0).y,width(),height());
		}
	}
};

struct Striped_Circle : Circle {
	Striped_Circle(Point p, int rr) : Circle(p, rr) {}

	void draw_lines() const {
		for(auto y = - r; y < r ; y++) {
			if (y % 4 == 0) {
				int dx = sqrt(pow(r,2) - pow(abs(y), 2));
				Line l(Point(center().x - dx, center().y + y),Point(center().x + dx, center().y + y));
				l.set_style(Line_style{Line_style::solid, 2});
				l.draw_lines();
			}
		}
		if (color().visibility()) {
			fl_color(color().as_int());
			fl_arc(point(0).x,point(0).y,r+r,r+r,0,360);
		}
	}
};

int main() {

	Point pt {100,100};

	Simple_window win {pt,600,400,"Canvas"};// make a simple window
	Immobile_Circle ic(	Point{175,200},100);
	Circle c(Point{275,200},100);
	ic.move(100,150);
	c.move(100,100);
	Striped_Rectangle rect(Point(200,100),100,200);
	Line l(Point(20,20),Point(200,20));

	Striped_Circle cs(Point{350,150},100);

	win.attach(cs);
	win.attach(l);
	win.attach(ic);
	win.attach(c);
	win.attach(rect);

	win.wait_for_button();// ghve control to the display engine


}
