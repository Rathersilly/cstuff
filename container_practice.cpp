
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <cmath>
using namespace std;

// doing ch9 of C++ Primer - containers stuff
//
void display(vector<double> x){

	for(auto i = x.begin(); i != x.end();i++) {
		cout << *i;
	}

}


int main() {
	//list<int> l = {1,2,3};
	vector<int> l = {1,2,3};
	vector<double> d;// = (l.begin(), l.end());
	for(auto i = l.begin();i!=l.end();i++) {
		d.push_back(*i);
	}
	cout << "hi" << endl;
	display(d);
	d.assign(l.begin(),l.begin() + 2);
	cout << "sup" << endl;
	display(d);
	cout << "sup" << endl;
	vector<int> v {1,2,3};

	for(auto i = v.begin(); i != v.end();i++) {
		cout << *i;
	}
	int x = 0;
	for(auto i = v.begin(); i != v.end();i++) {
		cout << *i;
	}
	v = {2,3,5,6};
	for(auto i = v.begin(); i != v.end();i++) {
		cout << *i << endl;
	}
	cout << v.size() << endl;
	cout << v.max_size() << endl;
	cout << v.empty() << endl;
	vector<string> s(3);
	for(auto i = s.begin(); i != s.end();i++) {
		cout << *i << endl;
	}
	
	
	vector<int> a = {1,2,3};
	vector<int> b = {1,2,3};
	list<int> c = {1,2,3};
	cout << (a == b) << endl;
	cout << "checking eq" << endl;
	auto j = c.begin();
	bool eq = false;
	for(auto i =a.begin();i !=a.end(); i++){ 

		cout << (*i == *j) << endl;
		j++;
		if (j == c.end()) {
			cout << "end of c" << endl;
		}

	}






}
