#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <cmath>
#include "goo.h"
using namespace std;



int main() {
	unsigned int prev = 0;
	unsigned int cur = 1;
	unsigned int next = prev + cur;

	cout << "int size: " << sizeof(next) << endl;
	long max_int = pow(2,  (sizeof(next)* 8));
	cout << "max # that can fit in unsigned int: " << max_int - 1 << endl;
	// Print out as many fibonacci numbers as will fit in an unsigned int
	while(cur + prev < max_int && cur + prev >= cur){
		cout <<  next << endl;
		prev = cur;
		cur = next;
		next = prev + cur;
	}
	cout << "the largest fib # that can fit in unsigned int is: " << cur << endl;
	

}
