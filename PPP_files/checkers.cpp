#include "Simple_window.h"// get access to our window library
#include "Graph.h"// get access to our graphics library facilities
using namespace Graph_lib;// our graphics facilities are in Graph_lib

// ch 14 ex - checkers board (for now)

struct Group : public Shape{
	Group () {
		int w= 50;
		int x = 0;
		int y = 0;
		for(int i = 0; i < 8;++i) {
			for(int j = 0;j < 8;++j) {
				//Rectangle* r = new Rectangle(Point{x+ i*w,y+j*w},w,w);
				Rectangle*  r = new Rectangle(Point{x+ i*w,y+j*w},w,w);
				//Rectangle* r = new Rectangle{Point{1,2},2,2};
				if((i + j) % 2 != 0) {
					r->set_fill_color(Color::dark_red);
					if (j == 0 || j == 1) {
						Circle* c = new Circle(Point{x+i*w + w/2,y+j*w + w/2}, w/4);
						c->set_fill_color(Color::blue);
						guys.push_back(c);
					}
					else if (j == 6 || j == 7) {
						Circle* c = new Circle(Point{x+i*w + w/2,y+j*w + w/2}, w/4);
						c->set_fill_color(Color::green);
						guys.push_back(c);
					}
				}
				squares.push_back(r);
			}
		}
		cout << squares.size() << endl;

	}
	//void move_guy(int row,int col) {


	void draw_lines() const {
		for(auto s : squares) {
		//for(auto s = squares.begin();s != squares.end();s++) {
			s->draw_lines();
		}
		for(auto g : guys) {
			g->draw_lines();
		}
	}

	

	vector<Rectangle*> squares;
	vector<Circle*> guys;


};
int main()
{

	Point pt {100,100};

	Simple_window win {pt,600,400,"Canvas"};// make a simple window

	Group g;
	win.attach(g);

	win.wait_for_button();// ghve control to the display engine


}
