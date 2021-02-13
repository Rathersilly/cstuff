#include <string>
#include <iostream>
#include <cctype>
#include <vector>
#include <stdexcept>
#include <cassert>
using namespace std;


	
// overloaded storeOn functions
// extern std::ostream& storeOn(std::ostream &, Screen &);
// extern BitMap& storeOn(bitMap &, Screen &);
//
// Screen class from C++ Primer ch 7
class Screen{
	// Window_mgr members can access the private parts of class Screen
	friend class Window_mgr;
	// friend std::ostream& storeOn(std::ostream&, Screen&; // last part of Primer 7.3 - idk if these are demoed in the book
	public:
		typedef std::string::size_type pos; 			// size_type can hold the max size of string on the system
		Screen() = default;
		Screen(pos ht, pos wd, char c): height(ht), width(wd),
										contents(ht * wd, c) { }
		Screen(pos ht, pos wd) : height(ht), width(wd), contents(ht * wd, ' ') { }
		char get() const { return contents[cursor]; }  	// get the character at the cursor (implicitly inline)
		inline char get(pos ht, pos wd) const; 			// explicitely inline
		Screen &move(pos r, pos c);

		Screen &set(char);
		Screen &set(pos, pos, char);

		// display overloaded on whether the object is const or not
		Screen &display(std::ostream &os)
							{ do_display(os); return *this; }
		const Screen &display(std::ostream &os) const
							{ do_display(os); return *this; }

	//private:
		pos cursor = 0;
		pos height = 0, width = 0;
		std::string contents;

		void do_display(std::ostream &os) const 		// function to do the work of displaying a Screen
							{ os << contents; }
};
// These functions that return &Screen can be used as lvalues!
inline Screen &Screen::move(pos r, pos c) {
	pos row = r * width;
	cursor = row + c;
	return *this;
}
char Screen::get(pos r, pos c) const {	// declared inline in the class
	pos row = r * width;				// compute row location
	return contents[row + c];			//return character at the given column
}
inline Screen &Screen::set(char c) {
	contents[cursor] = c; 				// set the new value at the current cursor location
	return *this;
}
inline Screen &Screen::set(pos r, pos col, char ch) {
	contents[r*width + col] = ch; 		//set specified location to given value
	return *this;
}


class Window_mgr {
	public:
		// location ID for each screen on the window
		using ScreenIndex = std::vector<Screen>::size_type;
		// reset the Screen at the given position to all blanks
		void clear(ScreenIndex);
	private:
		std::vector<Screen> screens{Screen(24, 80, ' ')};
};
void Window_mgr::clear(ScreenIndex i) {
	// s is a reference to the screen we want to clear
	Screen &s = screens[i];
	// reset the contents of that Screen to all blanks
	s.contents = string(s.height * s.width, ' ');
}

int main() {
	Screen s(5,10,'x');
	cout << s.contents;

	Screen t(5,6);
	cout << "hello" << endl;
	cout << t.contents << "hi" << endl;
	cout << s.get() << endl;
	cout << s.contents << endl;
	cout << s.get() << endl;
	s.set(0,5, 'X');
	cout << s.contents << endl;
	s.set(2,5, 'X');
	s.move(2,5);
	cout << s.cursor << endl;
	s.set('W');
	cout << s.get()<< endl;
	cout << s.contents << endl;
	s.move(2,7).set('#');
	cout << s.contents << endl;
	s.move(9,7).set('#'); 				// trying to set to string when out of range doesnt throw error
	cout << s.contents << endl;

	// examples of when different display() will be called based on constness
	Screen myScreen(5,3);
	const Screen blank(5, 3);
	myScreen.set('#').display(cout); 	// calls non const version
	blank.display(cout); 				// calls const version

	cout << endl;
	Screen myScreen2(5, 5, 'X');
	myScreen2.move(4, 0).set('#').display(cout);
	cout << endl;
	myScreen2.display(cout);
	cout << endl;

	Window_mgr m;
}
:q