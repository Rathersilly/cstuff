#include "Simple_window.h"// get access to our window library
#include "Graph.h"// get access to our graphics library facilities

int main()
{
using namespace Graph_lib;// our graphics facilities are in Graph_lib

// this library uses x,y = col,row
Point pt {100,100};

Simple_window win {pt,600,400,"Canvas"};// make a simple window

Line horiz{pt,Point{200,100}};
Line vert{Point{150,50},Point{150,150}};

Lines lns;
lns.add(Point{300,100}, Point{400,100});

int x_size =  win.x_max();
int y_size =  win.y_max();
int x_grid = 80;
int y_grid = 40;
Lines grid;
for(int x=x_grid;x<x_size;x+= x_grid) {
	grid.add(Point{x,0},Point{x,y_size});
}
for(int y=y_grid;y<y_size;y+= y_grid) {
	grid.add(Point{0,y},Point{x_size,y});
}
	
grid.set_color(Color::blue);
grid.set_style(Line_style{Line_style::dashdot, 2});

horiz.set_color(Color(99));

Open_polyline opl;
opl.add(Point {100,100});
opl.add(Point {150,200});
opl.add(Point {250,250});
opl.add(Point {300,200});

Closed_polyline cpl = {
	{200,200},{250,300},{350,350},{400,300}
};
cpl.set_style(Line_style{Line_style::dashdot, 4});

Rectangle rec00 {Point{150,100},200,100};
rec00.set_fill_color(Color::yellow);
Rectangle rec01 {Point{175,125},200,100};
rec01.set_fill_color(Color::white);
rec01.set_color(Color::invisible);
//rec00.move(175,125);

Vector_ref<Rectangle> vr;

for(int i = 0;i<16;++i) {
	for(int j = 0;j < 16;++j) {
		vr.push_back(new Rectangle{Point{i*20,j*20},20,20});
		vr[vr.size()-1].set_fill_color(Color{i*16 + j});
		win.attach(vr[vr.size()-1]);
	}
}

Text t {Point{250,350}, "hey whats going on over here?"};
t.set_color(Color::dark_red);

Circle c1{Point{500,300},50};
Circle c2{Point{450,250},100};
Ellipse e{Point{400,200},100,50};

win.attach(e);
win.attach(c1);
win.attach(c2);
win.attach(t);
win.attach(rec01);
win.attach(rec00);
win.put_on_top(rec01);
win.attach(grid);
win.attach(lns);
win.attach(horiz);
win.attach(vert);
win.attach(opl);
win.attach(cpl);

win.wait_for_button();// ghve control to the display engine
}

