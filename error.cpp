#include <iostream>
#include <string>
#include "string.h"
#include <typeinfo>
using namespace std;

// These are the exceptions listed in the ISO standard:
namespace std {
    class logic_error;
        class domain_error;
        class invalid_argument;
        class length_error;
        class out_of_range;
    class runtime_error;
        class range_error;
        class overflow_error;
        class underflow_error;
}

class MyErrorClass {};

void cause_error(){
		throw (out_of_range{"hi from cause_error"});
		cout << "This line won't be executed" << endl;
}

double divide(double a, double b) {
	cout << "in double divide" << endl;
	double c;
	// perhaps the caller should be in the try block, and the callee just throw
	try {
		c = a/b;
	}
	catch (out_of_range) {
		cout << "HANDLED" << endl;
	}
	catch (runtime_error &e) {
		cout << "Exception in divide()" << endl
			<< e.what();
		return 0;
	}
	return c;
}
int divide(int a, int b) {
	// apparently floating point zero division is not an exception in c++
	cout << "in int divide" << endl;
	int c;
	try {
		if (b == 0) {
			throw overflow_error("zero division");
		}
		cout << "after the throw" << endl;
		c = a/b;
	}
	//catch (overflow_error &e) {
	catch (exception &e) {
		cout << "in int divide again" << endl;
		cout << e.what() << endl;
	}
	return c;
}

void test() {
	int a[]{1,2,3}; 
	try {
		a[4] = 5;
		cout << "hi" << endl;
		throw(std::length_error{"hi from test()"});
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

	cout << "hi" << endl;

	cout <<	divide(3,4) << endl;
	cout <<	divide(3,0) << endl;
	
	cout << endl;
	try {
		cause_error();
	}
	catch (...){
		cout << "caught error" << endl;
	}
	try {
		throw MyErrorClass();
	}
	catch(MyErrorClass) {
		cout << "hey whats up" << endl;
	}
	cout << endl;

	test();
}
