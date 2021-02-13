#include <string>
#include <iostream>
#include <cctype>
#include <vector>
using namespace std;


int main() {

	unsigned cnt = 42; // not a constant expression
	constexpr unsigned sz = 42; // constant expression
	// constexpr see § 2.4.4 (p. 66)
	int arr[10]; // array of ten ints
	int *parr[sz]; // array of 42 pointers to int
	string bad[cnt]; // error: cnt is not a constant expression
	string strs[get_size()]; // ok if get_size is constexpr, error otherwise

	const unsigned size = 3;
	int ia1[sz] = {0,1,2}; // array of three ints with values 0, 1, 2
	int a2[] = {0, 1, 2}; // an array of dimension 3
	int a3[5] = {0, 1, 2}; // equivalent to a3[] = {0, 1, 2, 0, 0}
	string a4[3] = {"hi", "bye"}; // same as a4[] = {"hi", "bye", ""}
	int a5[2] = {0,1,2}; // error: too many initializers

	char s[10] = "hello";
	for(auto c : s) {
		cout << c << " ";
	}
	cout << endl;
	cout << s;
	s[sizeof(s)-1] = '!';
	s[sizeof(s)] = '\0';
	cout << endl;
	cout << s;
	

}
