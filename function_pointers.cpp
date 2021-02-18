#include <string>
#include <iostream>
#include <cctype>
#include <vector>
#include <stdexcept>
#include <cassert>
using namespace std;

void say(string = "hi");
// Note: decltype doesn't include default arguments
// which should have been obvious
typedef decltype(say) saytype;

int main() {
	void (*phi)(string);
	phi = say;
	say();
	say("ok");
	phi("phi");
	saytype *foo;
	foo = say;
	foo("foo");
	//goo();
	//goo("goo");
	//goo = say;
	


}

void say(string s) {
	cout << s << endl;
}

