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


int main() {
	try {
		throw runtime_error("hello");
	}
	catch (exception &e){

		cout << "hi" << endl;
		cout << e.what() << endl;
	}


		

}
