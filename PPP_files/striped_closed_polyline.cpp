#include "Simple_window.h"// get access to our window library
#include "Graph.h"// get access to our graphics library facilities
using namespace Graph_lib;// our graphics facilities are in Graph_lib

// ch 14 ex striped closed polyline - have scaffold in place but need
// more linear algebra first

struct Striped_Closed_Polyline : Closed_polyline {
	Striped_Closed_Polyline(initializer_list<Point> lst) : Closed_polyline(lst) {
		set_scaffold();



	}
	void draw_lines() const {
		//Closed_polyline::draw_lines();
		br->draw_lines();
		lines->draw_lines();
		//now for the stripes
		x = br->points(0).x
		for( auto y = br->points(0).y) {
			// if this is an actual point, handle it mb
			//if(points
			//lpt = first intersection
			//check if xy intersects with any line

	}

	Rectangle* br;
	Lines* lines;
	void set_scaffold();


	~Striped_Closed_Polyline() {
		delete br;
		delete lines;
	}
};
void Striped_Closed_Polyline::set_scaffold() {
		int xmin = 1000, ymin = 1000;
		int xmax = 0, ymax = 0; int i = 0;
		lines = new Lines;
		for(auto a = points.begin();a != points.end();++a) {
			if(a->x < xmin) { xmin = a->x; }
			if(a->y < ymin) { ymin = a->y; }
			if(a->x > xmax) { xmax = a->x; }
			if(a->y > ymax) { ymax = a->y; }
			cout << a->x << " " << i << endl;
			if (a + 1 != points.end()) {
				cout << "hi"<< a->x << " " << (a+1)->x << endl;
				lines->add(*a,*(a+1));
			}
			else {
				lines->add(*a,*(points.begin()));
			}
			++i;
		}
		br = new Rectangle(Point{xmin,ymin},xmax - xmin,ymax - ymin);
}



int main()
{

	Point pt {100,100};

	Simple_window win {pt,600,400,"Canvas"};// make a simple window

	//Closed_polyline spoly{{100,200},{250,200}, {300,300}};
	Striped_Closed_Polyline spoly{{100,200},{250,100}, {300,300}};
	win.attach(spoly);

	win.wait_for_button();// ghve control to the display engine


}
