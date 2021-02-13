#include <string>
#include <iostream>
#include <cctype>
#include <vector>
#include <stdexcept>
using namespace std;
using iter = std::vector<int>::iterator;

void print(vector<int> v) {
	std::vector<int>::iterator beg = v.begin();

	while(beg != v.end()) {
		cout << *beg << endl;
		beg++;
	}
	for(auto i = v.begin();i != v.end();i++) {
		cout << (*i  * *i) << endl;
	}

}
void recprint(iter b, iter e) {
	if (b != e) {
		cout << *b << endl;
		recprint(++b, e);
	}



}




int &get(int *arry, int index) { return arry[index]; }
int main() {
	int ia[10];
	for (int i = 0; i != 10; ++i)
	get(ia, i) = i;

	for(auto a : ia) {
		cout << a  << endl;
	}

	cout << "hihihi" << endl;
	vector<int> v {1,2,3,4};
	print(v);
	cout << "hihihi" << endl;
	recprint(v.begin(), v.end());
}

