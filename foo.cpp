#include <string>
#include <sstream>
#include <iostream>
//#include <fstream>
#include <vector>
//#include <list>
//#include <cmath>
//#include "goo.h"
#include <unistd.h>
using namespace std;

// ch 8 ppp exercises

void swap(int& a, int& b) { int t = a; a = b; b = t;}
void print(vector<int> v, string s = "hi there") {
	cout << s << endl;
	for(int i =0; i<v.size();i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}
void print(vector<string> v, string s = "hi there") {
	cout << s << endl;
	for(int i =0; i<v.size();i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}
vector<int> ssizes(vector<string> s) {
	vector<int> nums;
	for(auto a = s.begin();a != s.end();a++) {
		nums.push_back(a->length());
	}
	return nums;
}
void f(const int n)
{
//    ++n;  // cannot modify const argument
    cout << n << endl;
}



int main() {
	vector<string> s {"hi", "there"};
	vector<int> x;


	x = ssizes(s);
	print(s);
	print(x);
	try
{
    int n = 10;
    f(n);
}
catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
}
catch (...) {
    cerr << "exception\n";
}
}
