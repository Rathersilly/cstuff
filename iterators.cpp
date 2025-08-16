#include <string>
#include <iostream>
#include <cctype>
#include <vector>
using namespace std;


int main() {

	vector<int> foo(10, 0); 		// create vector of 10 0's

	// filling foo with even numbers
	int j = 1;
	for(auto fooIterator = foo.begin(); fooIterator != foo.end(); fooIterator++) {
		*fooIterator = j*2;
		++j;
	}
	for(int i : foo ) {
		cout << i << endl;
	}
	
	auto fooIterator = foo.begin();
	auto midPtr = foo.begin() + foo.size() /2;
	cout << "mid: " << *mid2 << endl;
	for( auto i = foo.begin(); i != foo.end();i++ ) {
		if (i < midPtr)
			cout << *i << endl;
		else
			cout << (*i) * 10 << endl;
	}
    
	// binary search with iterator:
	
	string text = "abcdefghi";
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
