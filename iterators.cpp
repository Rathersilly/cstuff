#include <string>
#include <iostream>
#include <cctype>
#include <vector>
using namespace std;


int main() {

	vector<int> a(10, 0);
	int j = 1;
	for(auto ai = a.begin(); ai != a.end(); ai++) {
		*ai = j*2;
		++j;
	}
	for(int i : a ) {
		cout << i << endl;
	}
	
	auto ai = a.begin();
	auto mid2 = a.begin() + a.size() /2;
	cout << "mid: " << *mid2 << endl;
	for( auto i = a.begin(); i != a.end();i++ ) {
		if (i < mid2)
			cout << *i << endl;
		else
			cout << (*i) * 10 << endl;
	}
    
	// binary search with iterator:
	
	string text = "abcde";
	auto beg = text.begin(), end = text.end();
	auto mid = beg + (end - beg) / 2;
	int i = 0;
	char sought = 'a';
	while (mid != end && *mid != sought) {
		if (sought < *mid)
			end = mid;
		else
			beg = mid + 1;
		mid = beg + (end - beg) / 2;
		i += 1;
	}
	cout << "times through loop: " << i << endl;
	cout << *mid << endl;
	
}
