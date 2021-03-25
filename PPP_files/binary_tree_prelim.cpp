#include "Simple_window.h"// get access to our window library
#include "Graph.h"// get access to our graphics library facilities
using namespace Graph_lib;// our graphics facilities are in Graph_lib

// ch 14 ex - binary tree prelim

struct Binary_tree : Shape {
	Binary_tree(int lev) :levels(lev){
		int x0 = 300;
		int y0 = 50;
		step = 40;
		r = 20;
		Circle* c = nullptr;
		if (levels >= 1) {
			c = new Circle({x0,y0},r);
			nodes.push_back(c);
		}
		//levels - 1 times make kids
		if (levels > 1) {

			create_kids(*c, levels - 1);
		}
		
	}
	void create_kids(const Circle& parent, int levels) {
	
					cout << "hello" << endl;
		if (levels == 0) return;

		int x0 = parent.center().x;
		int y0 = parent.center().y;
		cout << "x0:" << x0 << "y0: " << y0 << endl;
		Circle* c1 = new Circle({x0 - step*levels,y0 + step},r);
		Circle* c2 = new Circle({x0 + step*levels,y0 + step},r);

		// Note the following line doesnt work because of the Shape copy constructor
		// disallowing copying of parent.center()
		//Line* l1 = new Line(parent.center(),c1->center());

		Line* l1 = new Line({x0,y0},c1->center());
		Line* l2 = new Line({x0,y0},c2->center());
		lines.push_back(l1);
		lines.push_back(l2);
		nodes.push_back(c1);
		nodes.push_back(c2);
		create_kids(*c1, levels - 1);
		create_kids(*c2, levels - 1);
	}



	void draw_lines() const {
		for(auto a : nodes) {
			a->draw_lines();
		}
		for(auto a : lines) {
			a->draw_lines();
		}

	}

	int levels;
	int step;
	int r;
	vector<Circle*> nodes;
	vector<Line*> lines;

};


int main()
{

	Point pt {100,100};

	Simple_window win {pt,600,400,"Canvas"};// make a simple window

	Binary_tree b(4);
	win.attach(b);

	win.wait_for_button();// ghve control to the display engine


}
