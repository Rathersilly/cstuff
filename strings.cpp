// range-based for loop
#include <iostream>
#include <string>
#include "string.h"
using namespace std;

int main ()
{
	
	//char *a = "hello";   		this raises warning
	//const char *a = "hello";
	char *a = strdup("hello");
	cout << a << endl;
	cout << a[3] << endl;
	cout << &a << endl;

}

