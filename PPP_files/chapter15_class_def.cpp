#include "Simple_window.h"// get access to our window library
#include "Graph.h"// get access to our graphics library facilities
using namespace Graph_lib;// our graphics facilities are in Graph_lib

// ch 15 class definition drills

double one(double x){return x/2;}

struct Person {
	Person(string n,int a) : _name(n),_age(a) {
		string check_string = ";:\"\'[]*&^%$#@!";
		cout << _name << endl;
		for(int i = 0;i <check_string.size();i++) {
			cout << check_string[i] << endl;
			cout  << _name.find(check_string[i]) << endl;
			if (_name.find(check_string[i]) != string::npos) throw runtime_error("invalid name");
		}

		if (_age < 0 || _age > 150) throw runtime_error("age out of range");
	}
	Person() {}

	string name() const { return _name; }
	int age() const { return _age; }
	void name(const string& name) { _name = name; }
	void age(const int& age) { _age = age; }
	
private:
	string _name;
	int _age;
};
void operator<<(ostream& os,  Person p) {
	os << "Name: " << p.name() << ", Age: " << p.age() << endl;
}
void operator>>(istream& is, Person& p) {
	string n;
	int a;

	cout << "Enter name: ";
	is >> n;
	cout << "Enter age: ";
	is >> a;
	p.name(n);
	p.age(a);
}

int main()
{
	Point pt {100,100};


	Person p("Goofy",63);
	cout  << p;

	Person p2;

	cin >> p2;
	cout << p2;

	Person p3("Go;ofy",63);
	cout  << p3;

}
