#include <iostream>
#include <string>
#include "string.h"
#include <typeinfo>
#include <vector>
typedef int X;
using namespace std;

// Identity oriented - I think I like this one the best but holy shit how does this overload work?
// 					 - like how does the right function get called?
class Foo2
{
     X x_;
public:
          X & x()       { return x_; }
    const X & x() const { return x_; }
};
class Person {
	string name;
	string address;
	int age;
	public:
	Person(string name, string add,int a) : name(name), address(add), age(a) {}
	string getname() {
		return name;
	}

};

int main (int argc, char *argv[])
{

	Person bob ("bob", "123 fake st", 44);
	cout << bob.getname();


	




}
