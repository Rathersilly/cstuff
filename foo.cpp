#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// in Ch 9 of C++ Primer

vector<int>::iterator find(vector<int>::iterator beg,vector<int>::iterator end, int num) {
	while (beg != end) {
		if (*beg == num) {
			return beg;
		}
		beg++;
	}
	return end;
}



int main()
{
	int n = 5;
	vector<int> v{1,3,5,7};
	cout << *find(v.begin(), v.end(), n) << endl;
	n = 4;
	cout << *find(v.begin(), v.end(), n) << endl;
	//decltype(v) w(v.begin(), v.begin() + 3 );
	vector<int> w = {1,2,3,4};
	auto beg = w.begin();
	while (beg != w.end()) {
		cout << *beg << endl;
		++beg;
	}

}

