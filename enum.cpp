#include <iostream>
using namespace std;
enum Color { red, green, blue };

int main() {

	Color r;
	r = red;
	switch(r)
	{
	    case red  : cout << r << "red\n";   break;
	    case green: cout << "green\n"; break;
	    case blue : cout << "blue\n";  break;
	}
	
}
