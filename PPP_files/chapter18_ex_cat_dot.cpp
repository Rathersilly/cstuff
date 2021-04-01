#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
#include <string>
#include <string.h>
#include <sstream>
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

// ch 18 ex 5-7 - careful with the char* version of cat_dot
// - its super easy to forget to delete the allocated mem.

		
string cat_dot(const string& s1, const string& s2, const string& sep = ".") {
	INFO
	stringstream ss;
	ss << s1 << sep << s2;
	return ss.str();
}
char* at_dot(const char* s1,const char* s2,const char* sep = ".") {
	INFO
	int i = 0;
	const char* iter = s1;

	while(*iter) {i++;iter++;}
	iter = s2;
	while(*iter) {i++;iter++;}
	iter = sep;
	while(*iter) {i++;iter++;}
	char* memo = new char[i];
	iter = s1;
	i = 0;
	while(*iter) {
		*(memo+i) = *iter;
		++i;
		++iter;
	}
	iter = sep;
	while(*iter) {
		*(memo+i) = *iter;
		++i;
		++iter;
	}
	iter = s2;
	while(*iter) {
		*(memo+i) = *iter;
		++i;
		++iter;
	}

	return memo;


		
}

int main() {
	cout << cat_dot("hi","there");
	cout << cat_dot("sup","dog","my");



}
