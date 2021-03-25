#include <string>
//#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <iomanip>			// setprecision(n), setw
//#include <list>
//#include <cmath>
//#include "goo.h"
//#include <unistd.h>
//#include <climits>          /// INT_MAX
//#include <algorithm>
using namespace std;
struct A {
	A() {};
	A (int rr):r(rr) {

		cout << r;
	}
	int r;

};
struct B : public A {
	//B(int rr) : A(rr) { cout << r; }
};
//struct C : A{
//};


int main() {

	A a(1);
	B b(4);
	//C c(3);
	b.r = 5;
	cout << b.r;

	

}
