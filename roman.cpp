#include <string>
//#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
//#include <list>
//#include <cmath>
//#include "goo.h"
//#include <unistd.h>
//#include <climits>          /// INT_MAX
//#include <algorithm>
using namespace std;

// super basic roman numerals - no error checking or anything

string int_to_roman(int n);
class Roman_int {

	public:
	string str;

	int as_int();
	Roman_int(string s) : str(s) {}
	Roman_int(int i) ;

};
ostream& operator<<(ostream& os, Roman_int r) {
	return os <<  r.str ;
}
Roman_int operator+(Roman_int& a, Roman_int& b) {
	int sum = a.as_int() + b.as_int();
	return Roman_int(int_to_roman(sum));
}
int val(char c) {
	switch(c) {
		case 'i':
			return 1;
		case 'v':
			return 5;
		case 'x':
			return 10;
		case 'L':
			return 50;
		default:
			throw runtime_error("bad char");
	}
	return 0;
}
int Roman_int::as_int(){
	string s = str;
	char prev;
	char cur;
	int sum = 0;
	for(int a = 0;a < s.size();++a) {
		prev = str[a];
		if (a + 1 < s.size()) {
			cur = str[a+1];
		}
		else {
			sum += val(prev);
			return sum;
		}
		
		if (val(prev) < val(cur)) {
			sum += val(cur) - val(prev);
			++a;
		}
		else {
			sum += val(prev);
		}
	}
	return sum;
}

string int_to_roman(int n) {
	string s;
	while (n > 0) {
		if (n >= 10) {
			for(int i = 0;i < n / 10; i++) {
				s += "x";
				n -= 10;
			}
		}
		else if (n >= 9) {
			s += "ix";
			n -= 9;
		}
		else if (n >= 5) {
			s += "v";
			n -= 5;
		}
		else if (n >= 4) {
			s += "iv";
			n -= 4;
		}
		else {
			for(int i = 1;i = n; ++i) {
				s += "i";
				n -= 1;
			}
		}
	}
	return s;
}

int main() {

	Roman_int r("iv");;
	Roman_int r2("xiv");;
	cout << r << " + " << r2 << " = " << r + r2 << endl;
	for(int i = 0;i < 40;i++) {
		cout << int_to_roman(i) << endl;
	}

	r.str = "viii";
	cout << "Roman " << r <<  " equals " << r.as_int() << endl;
	r.str = "xiv";
	cout << "Roman " << r <<  " equals " << r.as_int() << endl;
	r.str = "ix";
	cout << "Roman " << r <<  " equals " << r.as_int() << endl;
}
