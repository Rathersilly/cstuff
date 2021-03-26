#include "Simple_window.h"// get access to our window library
#include "Graph.h"// get access to our graphics library facilities
using namespace Graph_lib;// our graphics facilities are in Graph_lib

// PPP ch 15 sections 15.1-15.4 - graphs

double one(double) { return 1; }
double slope(double x) { return x/2; }
double square(double x) { return x*x; }
double sloping_cos(double x) { return cos(x) + slope(x); }

int main()
{
	Point pt {100,100};
	int xmax = 600;
	int ymax = 400;
	Simple_window win {pt,xmax,ymax,"Function Graphing"};// make a simple window

	int xorig = xmax/2;
	int yorig = ymax/2;
	Point orig{xorig, yorig};
	int rmin = -10;
	int rmax = 11;
	int npoints = 400;
	int xscale = 30;
	int yscale = 30;
	int xlength = xmax-40;
	int ylength = ymax-40;

	Axis x{Axis::x,Point{20,yorig}, xlength,xlength/xscale,"one notch == 1"};
	Axis y{Axis::y,Point{xorig,ylength+20}, ylength,ylength/yscale,"one notch == 1"};
	x.set_color(Color::red);
	y.set_color(Color::red);

	Function s {one, rmin, rmax, orig, npoints,xscale, yscale};
	Function s2 {slope, rmin, rmax, orig, npoints,xscale, yscale};
	Function s3 {square, rmin, rmax, orig, npoints,xscale, yscale};
	Function s4 {sqrt, rmin, rmax, orig, npoints,xscale, yscale};
	Function s5 {sloping_cos, rmin, rmax, orig, npoints,xscale, yscale};

	// first c++ lambda expression
	Function s6 {[](double x){return sin(x*x);}, rmin, rmax, orig, npoints,xscale, yscale};
	// can specify return type if needed
	Function s6 {[](double x) -> double {return sin(x*x);},
					rmin, rmax, orig, npoints,xscale, yscale};

	s4.set_color(Color::blue);
	s5.set_color(Color::green);
	s6.set_color(Color::yellow);
	x.label.move(-160,0);
	x.notches.set_color(Color::dark_red);

	Function f1 {log, 0.000001, rmax, orig, npoints,xscale, yscale};
	Function f2 {sin, rmin, rmax, orig, npoints,xscale, yscale};
	f2.set_color(Color::blue);
	Function f3 {cos, rmin, rmax, orig, npoints,xscale, yscale};
	// exp function overflows - looks neat though so leaving it
	Function f4 {exp, rmin, rmax, orig, 200,xscale, yscale};
	f4.set_color(Color::magenta);

	Text ts {Point{100,yorig-40},"one"};
	Text ts2 {Point{100,yorig+yorig/2 - 20},"x/2"};
	Text ts3 {Point{xorig - 100,20},"x*x"};

	win.attach(s);
	win.attach(s2);
	win.attach(s3);
	win.attach(s4);
	win.attach(s5);
	win.attach(s6);
	win.attach(ts);
	win.attach(ts2);
	win.attach(ts3);
	win.attach(x);
	win.attach(y);
	win.attach(f1);
	win.attach(f2);
	win.attach(f3);
	win.attach(f4);

	win.wait_for_button();// ghve control to the display engine


}
