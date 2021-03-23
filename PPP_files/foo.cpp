#include "Simple_window.h"// get access to our window library
#include "Graph.h"// get access to our graphics library facilities

int main()
{
	using namespace Graph_lib;// our graphics facilities are in Graph_lib

Point tl {100,100};// to become top left corner of window

Simple_window win {tl,600,400,"Canvas"};// make a simple window

Polygon poly;// make a shape (a polygon)

poly.add(Point{300,200});// add a point
poly.add(Point{350,100});// add another point
poly.add(Point{400,200});// add a third point
poly.set_style(Line_style(Line_style::dash, 4));

poly.set_color(Color::red);// adjust properties of poly

win.attach (poly);// connect poly to the window

Axis xa {Axis::x, Point{20,300},280,10,"x axis"};
Axis ya {Axis::y, Point{20,300},280,10,"y axis"};
//xa.set_color(Color::cyan);
//ya.set_color(Color::green);
Function sine {sin,0,100,Point{20,150},1000,50,50};

Polygon poly2;
poly2.add(Point{200,100});
poly2.add(Point{300,300});
poly2.add(Point{400,200});
poly2.set_color(Color::blue);
poly2.set_style(Line_style::dash);

Rectangle r {Point{200,200},100,50};
r.set_fill_color(Color::yellow);

Closed_polyline poly_rect;
poly_rect.add(Point{100,50});
poly_rect.add(Point{200,50});
poly_rect.add(Point{200,100});
poly_rect.add(Point{100,100});
poly_rect.add(Point{50,75});
poly_rect.set_style(Line_style(Line_style::dash,2));
poly_rect.set_fill_color(Color::green);

Text t{Point{150,150}, "Hello, graphical world!"};
// this doesnt compile - Font is ambiguous
//t.set_font(Font::times_bold);
t.set_font_size(20);

Image ii{Point{100,50},"heysup.jpg"};
win.attach(ii);
//ii.move(100,200);

Circle c {Point{100,200},50};
Ellipse e {Point{100,200},75,25};
e.set_color(Color::dark_red);
Mark m{Point{100,200},'x'};

ostringstream oss;
oss << "screen size: " << x_max() << "*" << y_max()
	<< "; window size: " << win.x_max() << "*" << win.y_max();
Text sizes{Point{100,20},oss.str()};
Image cal{Point{225,225},"heysup.jpg"};
cal.set_mask(Point{40,40},200,150);


win.attach(c);
win.attach(m);
win.attach(e);
win.attach(sizes);
win.attach(cal);


win.attach(xa);
win.attach(ya);
win.attach(sine);
win.attach(poly2);
win.attach(r);
win.attach(poly_rect);
win.attach(t);


win.wait_for_button();// ghve control to the display engine
}

