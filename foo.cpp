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



	int x = 4;
	auto y = [&r = x, x = x + 1]()->int
	{
		r += 2;
		return x * x;
	}(); // updates ::x to 6 and initializes y to 25.
	cout << y;
}
