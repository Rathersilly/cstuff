
#include <string>
#include <sstream>
#include <iostream>
//#include <fstream>
#include <vector>
//#include <list>
//#include <cmath>
//#include "goo.h"
//#include <unistd.h>
using namespace std;


int main() {
	string s;
	vector<string> v;
	/*
	while(cin >> s) {
		cout << s << " ";
	}
	*/
	string x;
	cout << "hey" << endl;// << flush;
	for(int i = 0;i < 5;i++) {
		//cin >> x;
		cout << i << ": ";
		getline(cin,x);

		v.push_back(x);
	}
	cout << s;
	for(int i =0;i<v.size();i++) {
		cout << v[i] << " ";
	}
}
