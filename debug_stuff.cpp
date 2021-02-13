#include <string>
#include <iostream>
#include <cctype>
#include <vector>
#include <stdexcept>
#include <cassert>
//#define NDEBUG
using namespace std;


using iter = vector<int>::iterator;



void print(iter i, iter e) {
	if (i != e) {
		cout << *i << endl;
		cerr << "Hello from " << __func__ << " in " << __FILE__ << endl
			<< ".  We are at line " << __LINE__ << "!" << endl;
		
		print(++i, e);
	}
}

int main() {

	vector<int> v = {1,2,3,4,5};
	print(v.begin(), v.end());
	#ifndef NDEBUG
	cerr << "Hello from " << __func__ << " in " << __FILE__ << endl;
	#endif
	assert(v[3] == 900);


}

