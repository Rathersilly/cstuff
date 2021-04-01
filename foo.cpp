#include <string>
#include <string.h>
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
//#include <unistd.h> 		// usleep
#include <math.h>
#include <stdlib.h> 		// srand, rand
#include <typeinfo>			// typeid 
using namespace std;




class X {};


struct Y{};



int main() {

	X x;
	Y y;
	int a;
	char* asdf[10];
	cout << typeid(x).name() << endl;
	cout << typeid(y).name() << endl;
	cout << typeid(a).name() << endl;
	cout << typeid(asdf).name() << endl;
	//cout << ("X" == typeid(x)) << endl;




}
