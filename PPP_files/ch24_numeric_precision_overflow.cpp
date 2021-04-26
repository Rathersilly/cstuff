#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
// #include <string>
// #include <string.h>
// #include <sstream>
// #include <fstream>
// #include <vector>
// #include <fstream>
#include <iostream>
#include <iomanip>			// setprecision(n), setw
//#include <list>
//#include <cmath>
//#include "goo.h"
//#include <unistd.h>
//#include <climits>          /// INT_MAX
//#include <algorithm>
//#include <unistd.h> 		// usleep
#include <math.h>
#include <stdlib.h> 		// srand, rand
#include <typeinfo>			// typeid 
using namespace std;

// ch21 numeric precision and overflow

int main()
{
	float x = 1.0/333;
	float sum = 0;
	cout << GREEN << "showing float rounding errors" << RESET << endl;
	cout << "x = " << setprecision(15)<< x<<endl;
	for(int i=0;i<333;++i) sum += x;
	cout << setprecision(15)<< sum<<endl;

	x = 1.0/3;
	cout << "x = " << setprecision(15)<< x<<endl;
	sum = 0;
	for(int i=0;i<100;++i) sum += x;
	cout << setprecision(15)<< sum<<endl;

	x = 1.0/10;
	cout << "x = " << setprecision(15)<< x<<endl;
	sum = 0;
	for(int i=0;i<100;++i) sum += x;
	cout << setprecision(15)<< sum<<endl;

	x = 1.0/10;
	cout << "x = " << setprecision(15)<< x<<endl;
	sum = 0;
	for(int i=0;i<100;++i) sum += x;
	cout << setprecision(15)<< sum<<endl;

	short int y = 40000;
	int i = 10000000;
	cout << GREEN << "overflowing a short and an int: " << RESET << endl;
	cout << y << " " << i*i << endl;


	cout << GREEN << "playing with sizeof()" << RESET << endl;
	cout << "sizes: " << sizeof(int) << " " << sizeof(float) << endl;
	int a = 2100000009;
	float f = a;
	cout << setprecision(4) << a << ' ' << f << endl;
	cout << setprecision(15) << a << ' ' << f << endl;

	cout << GREEN << "behold: float to int truncation:" << RESET << endl;
	f = 2.8;
	a = f;
	cout << a << ' ' << f << endl;
	cout << GREEN << "DID YOU KNOW char is a really small int?" << RESET << endl;
	cout << GREEN << "sizeof(char) = " << sizeof(char) << RESET << endl;
	char c = 0;
	for(int i = 0;i<500;++i){
		cout << int(c++) << '\t';
	}


}
