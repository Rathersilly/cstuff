#include <string>
#include <string.h>
//#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
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

// ch 18 ex - careful of checking if(!ptr) when you mean if(!*ptr) for empty string
// oh and dont try tou cout nullptr or *nullptr !!!!!

char* strdup( const char* str) {
	int count = 0;
	const char* iter = str;
	while(*iter) {
		count++;
		iter++;
	}
	char* memo = new char[count];
	char* iter2 = memo;
	for(int i = 0; i<count;++i) {
		*iter2  = *(str + i);
		iter2++;
	}

	return memo;

}
char* findx(const char* s, const char* x) {
	//starting at s
	const char* ts = s;
	const char* tx = x;
	const char* start = s;
	int c = 0;
	while(*ts && *tx) {
		cout << c << endl;
		c++;
		if(*ts == *tx) {
			tx++;
			if(!*tx || *tx == '\0') {

				cout << endl << start << " " << *start << endl;
				cout << "returning maybe" <<endl;
				return const_cast<char*>(start);
			}

			ts++;
		}
		else {
			tx = x;
			ts++;
			start = ts;
		}
	}
	//return nullptr;
	char* hi = "hey there";
	return hi;
	throw runtime_error("was returning nullptr");
}

int strcmp(const char* s1,const char* s2) {
	while(*s1) {
		if(*s2 == NULL) {return 1;}
		if(*s1 < *s2) {return -1;}
		if(*s1 > *s2) { return 1; }
		s1++;
		s2++;
	}
	if(*s1 == *s2) {return 0;}
	if(*s1 == NULL) {return -1;}
	throw runtime_error("wtf");
}

		

	




int main() {

	char s[] = "hello there";
	cout << *s << endl;
	cout << s << endl;

	char* t = nullptr;
	t = strdup(s);
	
	cout << *t << endl;
	cout << t << endl;
	s[4] = 'X';
	cout << *s << endl;
	cout << s << endl;
	cout << *t << endl;
	cout << t << endl;

	cout << "111111111111" << endl;
	cout << findx("oh hi there", "hi") << endl;
	cout << findx("hi", "hi") << endl;
	cout << findx("abc", "hi") << endl;

	cout << "222222222222" << endl;
	cout << strcmp("oh hi there", "hi") << endl;
	cout << strcmp("hi", "hi") << endl;
	cout << strcmp("abc", "hi") << endl;
	cout << strcmp("", "") << endl;
	cout << strcmp("", "sdfs") << endl;
	cout << strcmp("sfd", "") << endl;
	cout << "" << endl;
	
	string s1 = "oh yo there";
	string s2 = "yo";
	cout << "333333333333" << endl;
	char* asdf = findx( "oh yo there", "yo");
	cout << asdf << endl;
	cout << "444444444444" << endl;
	cout << findx( "oh yo there", "yo") << endl;
	cout << "555555555555" << endl;
	cout << findx(s1.c_str(),s2.c_str()) << endl;
	cout << "goodbye" << endl;
	delete[] t;

}

