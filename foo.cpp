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
	virtual void v() {cout << "Av" << endl;}
	void f() {cout << "Af" << endl;}

	//virtual void pv() = 0;

};
struct B : A {
	void v() {cout << "Bv" << endl;}
	void f() {cout << "Bf" << endl;}
};
struct C : A{
	void v() const{cout << "Cv" << endl;}
	void f() {cout << "Cf" << endl;}
};
void call(A& x) {
	x.v();
	x.f();
}



int main() {

	A a;
	B b;
	C c;
	call(a);
	call(b);
	call(c);

	

}
