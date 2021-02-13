#include <string>
#include <iostream>
#include <cctype>
#include <vector>
#include <stdexcept>
#include "foo.h"
using namespace std;

//int fun(int);

// Catching zero division error message
//https://stackoverflow.com/questions/6121623/catching-exception-divide-by-zero
void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}
void swap_pointy(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main() {
	int i = 2, j = 5;
	swap(i,j);
	cout << i << " " << j << endl;
	i = 10, j = 20;
	swap_pointy(&i,&j);
	cout << i << " " << j << endl;



}

int fun(int i) {
	return i * i;
}

