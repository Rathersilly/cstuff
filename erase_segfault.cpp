
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <list>
#include <cmath>
using namespace std;

// doing ch9 of C++ Primer - containers stuff
// erase is doing wonkythings - segfault
void display(deque<int> x){

	for(auto i = x.begin(); i != x.end();i++) {
		cout << *i << " ";
	}
	cout << endl;

}


int main() {
	vector<double> a = {9.2,8.5,7.3};

	deque<int> d = {1,2,3,4,5,6,7};
	display(d);
	d.push_front(0);
	d.push_back(4);
	display(d);
	d.insert(d.begin() + 2,9);
	d.insert(d.end() - 1,{123});
	display(d);
	d.insert(d.end(),a.begin(),a.end());
	d.insert(d.end(),1,666);
	display(d);

	cout << a.front() << endl;
	cout << a.back() << endl;
	cout << a.at(2) << endl;
	cout << a[2] << endl;
	//true
	cout << (*a.begin() == a.front()) << endl;
	
	


	for(auto a = d.begin();a!=d.end();a++){
		cout << "start" << endl;
			cout << *a << " ";
			cout << (*a== 666) << " ";
			cout << endl;

		if(*a %2== 0) {
			//cout << *a << " ";
			d.erase(a);
		}
	}
	cout << "hi" << endl;
	//ok this is weird - all evens got erased but only 2 666s got erased
	for(auto a = d.begin();a!=d.end();a++){
		cout << *a << " ";
	}
	cout << endl;





}
