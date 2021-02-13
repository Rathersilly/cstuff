#include <string>
#include <iostream>
#include <cctype>
#include <vector>
using namespace std;


int main() {
	vector<int> v;
	for(int i = 0;i < 10;i++) {
		v.push_back(i);
	}
	for (auto &i : v) {
		i *= i;
	}
	for(int i = 0;i < 10;i++) {
		cout << v[i] << endl;
	}
		cout << v.size() << endl;


    
}
