#include <string>
#include <sstream>
#include <iostream>
//#include <fstream>
#include <vector>
//#include <list>
//#include <cmath>
//#include "goo.h"
using namespace std;

// ch 8 ppp exercises

void print(vector<int> v, string s) {
	cout << s << endl;
	for(int i =0; i<v.size();i++) {
		cout << v[i] << endl;
	}
}
void fib(vector<int>& v,int n,int x=0,int y=1) {
	v.push_back(x);
	v.push_back(y);
	int next;
	for(int i = 0;i < n;i++) {
		next = x+y;
		if(next < 0) {
			stringstream msg;
			msg << y << " is the largest fib # that can fit in an int";
			throw overflow_error(msg.str());
		}
		v.push_back(next);
		x = y;
		y = next;
	}
}

int main() {
	vector<int> v;
	try {
		fib(v, 50);
	}
	catch (overflow_error& e) {
		cout << e.what() << endl;
	}
	string s = "heres some nums";
	print(v, s);

}
