
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <list>
#include <cmath>
using namespace std;

// doing ch9 of C++ Primer - containers stuff
//
void display(deque<int> x){

	for(auto i = x.begin(); i != x.end();i++) {
		cout << *i << " ";
	}
	cout << endl;

}


int main() {
	vector<double> a = {9.2,8.5,7.3};

	deque<int> d = {1,2,3};
	display(d);
	d.push_front(0);
	d.push_back(4);
	display(d);
	d.insert(d.begin() + 2,9);
	d.insert(d.end() - 1,{123});
	display(d);
	d.insert(d.end(),a.begin(),a.end());
	d.insert(d.end(),4,666);
	display(d);

	cout << *a.front() << endl;
	cout << *a.back() << endl;
	cout << *a.at(2) << endl;
	cout << *a[2] << endl;



}
