#include <string>
#include <string.h>
//#include <sstream>
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
using namespace std;

int ga[10];
vector<int> gv(10);

void f(int a[],int max) {
	int la[10];
	for(int i = 0;i<10;++i) {
		la[i] = ga[i];
		cout << la[i];
	}
	int* p = new int[max];
	for(int i = 0;i<max-1;++i) {
		p[i] = a[i];
	}
	cout << endl;
	for(int i = 0;i<max-1;++i) {
		cout << p[i] << " ";
	}
	delete[] p;
}

void f(vector<int> v) {
	vector<int> lv(v.size());
	for(int i = 0;i<v.size(); ++i) {
		lv[i] = v[i];
	}
	cout << "hi " << endl;
	for(int i = 0;i<v.size(); ++i) {
		cout << lv[i];
	}
	vector<int> lv2 = lv;
	vector<int> lv3{lv};
	cout << "asdf" << (lv2==lv3) << endl;
}





int main() {
	for(int i = 0;i<10;++i) {
		ga[i] = pow(2,i);
		gv[i]  = pow(2,i);
	}

	for(int i = 0;i<10;i++) {
		cout << ga[i] << endl;
	}
	int aa[10];
	for(int i = 0;i<10;i++) {
		cout << aa[i];
		aa[i] = 4*i;	
	}
	cout << "---------" << endl;
	for(int i = 0;i<10;i++) {
		cout << gv[i] << endl;
	}
	cout<<  "---------" << endl;

	
	f(ga,10);
	f(gv);


}
