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

// PPP ch 11 exercises - customizing io

string novowels(const string& s){
	vector<char> vowels {'a','e','i','o','u'};
	string memo;
	bool vflag = false;
	for(auto c : s) {
		vflag = false;
		for(auto v : vowels) {
			if (c == v) {
				vflag = true;
			}
		}
		if(vflag == false) memo += c;
	}
	return memo;
}
string replacevowels(const string& s, char rep) {
	vector<char> vowels {'a','e','i','o','u'};
	string memo;
	bool vflag = false;
	for(auto c : s) {
		vflag = false;
		for(auto v : vowels) {
			if (c == v) {
				vflag = true;
			}
		}
		if(vflag == false) memo += c;
		else memo += rep;
	}
	return memo;
}
vector<string> split(const string& s) {
	string memo;
	vector<string> vec;
	for(auto c : s) {
		if (c == ' ' || c == '\n') {
			if(memo != "") {
				vec.push_back(memo);
				memo = "";
			}
		}
		else {
			memo += c;
		}
	}
	if(memo != "") vec.push_back(memo);
	return vec;

}

int main() {
	int year = 1990;
	cout << year << endl;
	cout << showbase << oct << setw(8) << year << endl;
	cout << hex << setw(8)<< year << endl;
	cout << year << setw(8)<< endl;

	string s;

	ifstream is("input.txt");
	ofstream os("output.txt");
	while(is >> s) {
		os << novowels(s);
	}

	is.clear();
	is.seekg(0);
	// printing character classifacations
	while(is >> s) {
		for(auto c : s) {
			if(isalpha(c)) cout << c << " is alpha" << endl;
			else if(isdigit(c)) cout << c << " is num" << endl;
			else cout << c << " is something else" << endl;
		}
	}
	is.clear();
	is.seekg(0);

	while(is >> s) {
		cout << replacevowels(s, 'X');
	}
	is.close();
	string filename = "input.txt";
	ifstream bis(filename, ios_base::binary);
	bis.seekg(0,bis.end);
	int length = bis.tellg();
	cout << endl;
	cout << filename << " has a length of " << length << endl;
	cout << filename << " has a length of " << dec << length << endl;
	bis.seekg(0,bis.beg);
	char c;
	int a;
	while(bis >> c) {
		cout << c << flush;

	}
	bis.clear();
	bis.seekg(0,bis.beg);
	cout << "hi" << endl;
	vector<char> buffer(istreambuf_iterator<char>(bis),{});
	cout << endl << "hi" << endl;
	for(auto x : buffer) {
		cout << x;
	}
	//reversing and printing to file
	ofstream ofs("tuptuo.txt");
	for(auto a = buffer.crbegin();a != buffer.crend();a++) {
		ofs << *a;
	}



	cout << "split function" << endl;
	vector<string> foo = split("why hello there\nyou silly being");
	for(auto x : foo) {
		cout << x << endl;
	}




}
