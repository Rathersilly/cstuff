#include <iostream>
#include <string>
#include "string.h"
#include <typeinfo>
#include <vector>
using namespace std;

void print(initializer_list<string> s) {
	auto beg = s.begin();
	while (beg != s.end()) {
		cout << *beg << endl;
		++beg;
	}
	for(auto i = s.begin();i != s.end(); i++){
		cout << *i << endl;
	}
}

int main (int argc, char *argv[])
{
	string s1 = "hello";
	string s2 = "there";
	initializer_list<string> si{s1,s2};
	print(si);






}
