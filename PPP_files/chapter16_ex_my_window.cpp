//#define INFO cout << '\t' << __PRETTY_FUNCTION__ << " - " << __FILE__ << " - "<< __DATE__ << endl;
#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include "GUI.h"
#include <stdlib.h> 			// rand
#include <typeinfo>				// typeid
using namespace std;
using namespace Graph_lib;

// ch 16 exercise - My_window

class My_window : public Graph_lib::Window {
public:
	My_window(Point xy, int w,int h, const string& title)
		: Window(xy,w,h,title),
		next_button(Point{x_max() - 100,0},100,50,"Next",cb_next),
		quit_button(Point{x_max() - 100,50},100,50,"Quit",cb_quit) {
			attach(next_button);
			attach(quit_button);
			button_status = status::NONE;
			for(int i = 0;i<8;++i) {
				for(int j = 0;j<8;++j) {
					Rectangle* r = new Rectangle(Point{i*50,j*50},50,50);
					attach(*r);
					shapes.push_back(r);

				}

			}
			cout  << typeid(shapes[0]).name() <<  endl;
		}




	vector<Shape*> shapes;
	vector<int> colors;

	Button next_button;
	Button quit_button;
	int button_status;
	void wait_for_button() {
		INFO
		while (button_status == status::NONE) Fl::wait();
		button_status = status::NONE;
		cout << "redrawing" << endl;
		Fl::redraw();
	}
private:
	enum status { NONE, NEXT, QUIT };
	static void cb_next(Address, Address addr) { static_cast<My_window*>(addr)->next();}
	static void cb_quit(Address, Address addr) { static_cast<My_window*>(addr)->quit();}

	void next()
	{
			INFO
		button_status = status::NEXT;
		for(auto s : shapes) {
			s->set_fill_color(rand() % 256);
			//s->set_fill_color(Color::yellow);

		}
		/*res
		while(true) {
			int x = rand()%64;
			if (typeid(squares[x]) == 

					*/


	}

	void quit()
	{
		exit(0);
		button_status = status::QUIT;
	}

};




int main() {
	Point pt{100,100};
	My_window win(pt,600,400,"Hello");




	while(true)
	{
		win.wait_for_button();
	}

	//return gui_main();
	

	
}
