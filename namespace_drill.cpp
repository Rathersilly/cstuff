#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <cmath>
#include "goo.h"
using namespace std;

// ch 8 PPP

namespace X {
	int var;
	void print();
}
namespace Y {
	int var;
	void print();
}
namespace Z {
	int var;
	void print();
}


int main() {
	X::var = 7;
	X::print();
	using namespace Y;
	var = 9;
	print();
	{	using Z::var;
		using Z::print;
		var = 11;
		print();
	}
	print();
	X::print();




}
void X::print() { cout << var << " in X" << endl;}
void Y::print() { cout << var << " in Y" << endl;}
void Z::print() { cout << var << " in Z" << endl;}
