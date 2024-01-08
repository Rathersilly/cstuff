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
void print(vector<int> v, string s) {
	cout << s << endl;
	for(int i =0; i<v.size();i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}
vector<int> rev1(const vector<int>& v) {
	vector<int> x;
	for(auto i = v.begin();i != v.end() ;i++) {
		x.push_back(*i);
	}
	for(auto i = v.end() - 1;i != v.begin() - 1;i--) {
		x.push_back(*i);
	}
	for(auto  i = v.rbegin();  i!=v.rend();i++) {
		x.push_back(*i);
	}
	for(auto  i = v.crbegin();  i!=v.crend();i++) {
		x.push_back(*i);
	}
	vector<int>::size_type i = v.size();
	cout << i << endl;
	while (true) {
		i--;
		cout << i << endl;
		cout << v[i] << endl;
		x.push_back(v[i]);
		if (i == 0) break;
	}
	return x;
}
void rev2(vector<int>& v) {
	for(int i = 0; i < v.size()/2;i++) {
	}
	auto i = v.begin();
	auto j = v.end()-1;
	while (i < j)  {
		swap(*i,*j);
		i++;
		j--;
	}
}


		

int main() {
	vector<int> v {1,3,5,7,9};
	vector<int> z {1,3,5,7,9, 11};
	vector<int> x;
	string s = "heres some nums";
	x = rev1(v);
	print(v, s);
	print(x, s);
	rev2(v);
	print(v, s);
	rev2(z);
	print(z, s);

}
