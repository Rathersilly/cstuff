#include <string>
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
using namespace std;

// reading PPP ch 11

int main() {
	// these 2 statements are equal:
	//ofstream ofs("output.txt", ios_base::app);
	ofstream ofs{"output.txt", ios_base::app};
	ofs << "hello there" << endl;
	fstream fs{"output.txt", ios_base::in|ios_base::out};
	fs << "hi there" << endl;
	fs.close();
	int x = ofs.tellp();
	cout << x << endl;
	ofs.seekp(0, ofs.beg);
	x = ofs.tellp();
	cout << x << endl;
	ofs.seekp(12);
	x = ofs.tellp();
	cout << x << endl;
	char c = 'X';
	ofs << c;

	ofs.seekp(0, ofs.beg);
	ofs << c;
	x = ofs.tellp();
	cout << x << endl;
	// so it seems you cant go before the previous end when appending?
	// yep thats the case - app will always seek to end before writing:
	// https://stackoverflow.com/questions/18805924/seekp-not-going-to-required-position
	ofs.close();
	ofs.open("output.txt", ios_base::ate);
	cout << "----------------" << endl;
	x = ofs.tellp();
	cout << x << endl;
	ofs.seekp(0, ios_base::beg);
	x = ofs.tellp();
	cout << x << endl;
	ofs.write("WTF", 3);
	

	
	
}

