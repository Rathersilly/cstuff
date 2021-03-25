#include "Simple_window.h"// get access to our window library
#include "Graph.h"// get access to our graphics library facilities
using namespace Graph_lib;// our graphics facilities are in Graph_lib

// ch 14 ex - octagon - ended up with constructor taking top left bounding
// square coord and span length

struct Octagon : Closed_polyline {
	// how to construct? just truncate square? could inherit from rect
	// its kinda like a closed polyline also - that is better solution
	// for collision probs - can reuse its drawlines
	Octagon(Point xy, int ss) : p(xy),s(ss) {
		// just add points here 
		int a = s / (1+ sqrt(2));
		int a2 = a / sqrt(2);
		cout << "a: " << a << ", a2: " << a2 << endl;

		int x = p.x;
		int y = p.y;
		
		add({x,y+a2});
		

		cout << "ok" << endl;
		add({x+a2,y});
		add({x+a2 + a,y});
		add({x+ s - a2,y});
		add({x+ s,y+a2});
		add({x+ s,y+a2+a});
		add({x+ s-a2,y+s});
		add({x+ a2,y+s});
		add({x,y+a2+a});
	}


	Point p;
	int s;




};

int main()
{

	Point pt {100,100};

	Simple_window win {pt,600,400,"Canvas"};// make a simple window
	Octagon oct({200,200},100);

	win.attach(oct);

	win.wait_for_button();// ghve control to the display engine


}
