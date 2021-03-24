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
	A(int x) :n(x) {}


	int n;

};
ostream& operator<<(ostream& os, A& a) {
	return os << a.n << endl;
}
int main() {

	A a{1};
	A b(2);
	A c = {3};
	A d = 4;

	cout << a;
	cout << b;
	cout << c;
	cout << d;


	

}

