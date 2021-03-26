#include "Simple_window.h"// get access to our window library
#include "Graph.h"// get access to our graphics library facilities
using namespace Graph_lib;// our graphics facilities are in Graph_lib

// PPP ch 15 section 15.5 - ran into a problem sending lambda with captures to Function
// constructor: https://groups.google.com/g/ppp-public/c/WBHYlwS6m3g

int fac(int n) {
	int memo = 1;
	for(int i = 1;i <= n;++i) {
		memo *= i;
	}
	return memo;
}
double term(double x, int n) { return pow(x,n)/fac(n); }

double expe(double x, int n) {
	double sum = 0;
	for (int i = 0;i<n;++i) { sum += term(x,i); }
	return sum;
}





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

	Function real_exp {static_cast<double (*)(double)>(exp), rmin, rmax, orig, npoints,xscale, yscale};
	real_exp.set_color(Color::blue);
	win.attach(real_exp);

	for(int n = 0;n<50;++n) {
		ostringstream ss;
		ss << "exp approximation; n==" << n;
		win.set_label(ss.str());
		//Function e {[n](double x){return expe(x,n);}, rmin,rmax,orig,200,xscale,yscale};
		//Function e([n](double x){return sin(x*n);}, rmin, rmax, orig, npoints,xscale, yscale);
		Function e(sin, rmin,rmax,orig,200,xscale,yscale);
		//Function e {cos, rmin, rmax, orig, npoints,xscale, yscale};
		win.attach(e);
		win.wait_for_button();
		win.detach(e);
	}

	win.wait_for_button();// ghve control to the display engine


}
