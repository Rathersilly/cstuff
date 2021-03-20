#include <string>
//#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
//#include <list>
//#include <cmath>
//#include "goo.h"
//#include <unistd.h>
//#include <climits>          /// INT_MAX
//#include <algorithm>
using namespace std;

// PPP ch 10 (iostreams) exercises

class Roman_int {

	public:
	string str;

	int as_int();
	Roman_int(string s) : str(s) {}
	Roman_int(int i) ;

};
ostream& operator<<(ostream& os, Roman_int r) {
	return os <<  r.str ;
}
int Roman_int::as_int(){
}



int main() {

	Roman_int r("xii");;

	cout << "Roman " << r <<  " equals" << r.as_int() << endl;
}
