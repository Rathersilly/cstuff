#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#include <string>
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
// #include <stdlib.h> 		// srand, rand
// #include <typeinfo>			// typeid 

using namespace std;

char* strdup(const char* c)
{
	int n = 0;
	while(c[n]) {
		n += 1;
	}

	char* newstr = new char[n];
	for(int i = 0; i < n;++i) {
		newstr[i] = c[i];
	}

	return newstr;
		
}

char* findx(char* s,const char* x)
{
	int n = 0;
	while(s[n]) {
		if (s[n] == x[0]) {
			// loop until either chars or not equal, or reach end of one of the strings
			int i = 0;
			while(s[n + i] && x[i] && s[n+i] == x[i]) {
				++i;
				if (!x[i]) {
					return s + n;
				}
			}
		}
		++n;
	}
	return nullptr;
}

int strcmp(const char* s1, const char* s2)
{
	int i = 0;
	while(s1[i]) {
		if (!s2[i]) { return 1; }
		else if (s1[i] < s2[i]) { return -1; }
		else if (s2[i] < s1[i]) { return 1; }
		++i;
	}
	if (s2[i]) { return -1;}
	return 0;
}




string catdot(const string& s1,const string& s2,char separator = '.')
{
	string memo = s1 + separator + s2;


	return memo;
}





int main()
{
	char str[] = "hello";
	char* newstr = strdup(str);
	cout << str << endl;
	cout << newstr << endl;
	newstr[3] = 'x';
	
	cout << "***" << endl;
	cout << str << endl;
	cout << "###" << endl;
	cout << newstr << endl;

	char s[] = "ll";
	char* found = findx(str,s);
	cout << found  << endl;
	char str2[] = "hello";
	cout << strcmp(str,str2)  << endl;
	cout << strcmp(str,s)  << endl;

	string s1 = "hello";
	string s2 = "world";
	cout << s1.length() << endl;
	cout << catdot(s1,s2,'X') << endl;
}
