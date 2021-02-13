#include <string>
#include <iostream>
#include <cctype>
#include <vector>
#include <stdexcept>
#include <cassert>
//#define NDEBUG
using namespace std;

using iter = vector<int>::iterator;
class Person {
	string name;
	int age;
	public:

	string &Name () { return name; };
	const string &Name () const { return name; }

};

	


int main() {
	Person bob;
	bob.Name() = "bob";
	cout << bob.Name();


}

