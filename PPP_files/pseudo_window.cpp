#include "Simple_window.h"// get access to our window library
#include "Graph.h"// get access to our graphics library facilities
using namespace Graph_lib;// our graphics facilities are in Graph_lib

// ch 14 ex - pseudo window

struct Pseudo_window : public Shape{
	Pseudo_window (Point p, int ww, int hh, int cr = 0) : h(hh),w(ww),corner_radius(cr) {
		add(p);
		int button_border = 10;
		int button_w = 20;
		Rectangle* outside = new Rectangle(p,w,h);
		Rectangle* menubar = new Rectangle(p,w,40);
		Rectangle* xsquare = new Rectangle({p.x +w - button_border - button_w,p.y + button_border},\
				button_w,button_w);
		Mark* x = new Mark({p.x +w - button_border - (button_w/2),p.y + button_border+ button_w/2}, 'X');
		menubar->set_fill_color(Color::blue);
		xsquare->set_color(Color::white);
		x->set_color(Color::white);
		elem.push_back(outside);
		elem.push_back(menubar);
		elem.push_back(xsquare);
		elem.push_back(x);
		
	}

	void draw_lines() const {
		for(auto e : elem) {
		//for(auto s = squares.begin();s != squares.end();s++) {
			e->draw_lines();
		}
	}



	int h;
	int w;
	int corner_radius;
	vector<Shape*> elem;


};
int main()
{

	Point pt {100,100};

	Simple_window win {pt,600,400,"Canvas"};// make a simple window

	Pseudo_window g({50,50},200,200);
	win.attach(g);

	win.wait_for_button();// ghve control to the display engine


}
