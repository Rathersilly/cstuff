#include "Simple_window.h"// get access to our window library
#include "Graph.h"// get access to our graphics library facilities
using namespace Graph_lib;// our graphics facilities are in Graph_lib

// ch 15.6 graphing population data

struct Distribution {
	int year, young, middle, old;
};
istream& operator>>(istream& is, Distribution& d) {
	char ch1 = 0;
	char ch2 = 0;
	char ch3 = 0;
	Distribution dd;
	if(is >> ch1 >> dd.year
			>> ch2 >> dd.young >> dd.middle >> dd.old
			>> ch3) {
		if(ch1!= '(' || ch2 != ':' || ch3 != ')') {
			is.clear(ios_base::failbit);
			return is;
		}
	}
	else {
		return is;
	}
	d = dd;
	return is;
};
class Scale { 				// data value to coordinate conversion
	int cbase;				// coordinate base
	int vbase;				// base of values
	double scale;
	public:
	Scale(int b, int vb, double s) : cbase(b),vbase(vb),scale(s) {}
	int operator()(int v) const {return cbase + (v-vbase)*scale; }		//see S21.4
};

int main()
{
	constexpr int base_year = 1960;
	constexpr int end_year = 2040;
	string filename = "age_data.txt";
	//string filename = "asdjkfl;skfjdage_data.txt";
	

	Point pt {100,100};
	int xmax = 600;
	int ymax = 400;
	int xoffset = 100;
	int yoffset = 60;
	int xspace = 40;
	int yspace = 40;
	int xlength = xmax-xoffset - xspace;
	int ylength = ymax-yoffset - yspace;
	double xscale = double(xlength)/(end_year - base_year);
	double yscale = double(ylength)/100;

	Scale xs {xoffset,base_year,xscale};
	Scale ys {ymax - yoffset,0,-yscale};

	Simple_window win {pt,xmax,ymax,"Aging Japan"};// make a simple window
	Axis x {Axis::x,Point{xoffset,ymax-yoffset},xlength,(end_year-base_year)/10,
		"year    1960    1970    1980    1990    "
		"2000    2010    2020    2030    2040"};
	x.label.move(-100,0);
	Axis y {Axis::y,Point{xoffset,ymax-yoffset},ylength,10,"% of population"};
	Line current_year {Point{xs(2008),ys(0)},Point{xs(2008),ys(100)}};
	current_year.set_style(Line_style::dash);

	Open_polyline children;
	Open_polyline adults;
	Open_polyline aged;
	ifstream ifs{filename};
	if(!ifs) throw runtime_error("cant open that file");
	for(Distribution d; ifs>>d;) {
		//etc error checking
		if(d.year<base_year || end_year<d.year) throw runtime_error("year out of range");
		if(d.young+d.middle+d.old != 100) throw runtime_error("ages dont add up");
		const int x = xs(d.year);
		children.add(Point{x,ys(d.young)});
		adults.add(Point{x,ys(d.middle)});
		aged.add(Point{x,ys(d.old)});
	}
	Text children_label{Point{20,children.point(0).y},"age 0-14"};
	children.set_color(Color::red);
	children_label.set_color(Color::red);
	Text adults_label{Point{20,adults.point(0).y},"age 15-64"};
	adults.set_color(Color::green);
	adults_label.set_color(Color::green);
	Text aged_label{Point{20,aged.point(0).y},"age 65+"};
	aged.set_color(Color::blue);
	aged_label.set_color(Color::blue);


	win.attach(x);
	win.attach(y);
	win.attach(current_year);
	win.attach(children);
	win.attach(adults);
	win.attach(aged);
	win.attach(children_label);
	win.attach(adults_label);
	win.attach(aged_label);

	win.wait_for_button();// ghve control to the display engine
}
