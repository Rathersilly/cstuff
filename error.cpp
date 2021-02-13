#include <iostream>
#include <string>
#include "string.h"
#include <typeinfo>
using namespace std;
struct foo {};
void cause_error(){
		throw (out_of_range{"hi"});
}

double divide(double a, double b) {
	try {
		cause_error();
	}
	catch (out_of_range) {
		cout << "HANDLED" << endl;
	}
	return a/b;
}

void test(){		//c++ Tour 3.4
	int a[]{1,2,3}; 
	try {
		a[4] = 5;
		cout << "hi" << endl;
		throw(std::length_error{"hihi"});
	}
	catch (std::length_error) {
		cout << "test failed: length error\n";
		throw;    //rethrow
	}
	catch (std::bad_alloc) {
		//Ouch! test() is not designed to handle memory exhaustion
		std::terminate();//terminate the program
	}
}
int main ()
{
	//static_assert(asdf != 3,"ITS NOT 3");
	int a = 3, b = 4;
	decltype(a) c = a;
	decltype(a = b) d = a;

	cout <<   a << " " << b << endl;
	cout <<   c << " " << d << endl;
	//cout <<  i  << " " << j << endl;



	cout << "hi" << endl;

	cout <<	divide(3,4) << endl;
	//cause_error();

	test();
}
