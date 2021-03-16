#include <string>
#include <sstream>
#include <iostream>
//#include <fstream>
#include <vector>
#include <fstream>
//#include <list>
//#include <cmath>
//#include "goo.h"
//#include <unistd.h>
//#include <climits>          /// INT_MAX
//#include <algorithm>
//#include <temp.h>
#include "temp.h"
using namespace std;

// Reading PPP ch 10 - iostreams

Day::Day() : hour(24) {
	for (int i = 0; i<hour.size(); ++i) {
		hour[i] = not_a_reading;
	}
}
Month::Month() : month(not_a_month), day(32) {}
Year::Year() : month(12) {}

void end_of_loop(istream& is, char term, const string& message) {
	if (is.fail()) {
		is.clear();
		char ch;
		cout << "in eol: ";
		if (is >> ch && ch == term) {
			cout << "returning ok" << endl;
			return;
		}
		cout << "in eol2: ";
		cout << ch << endl;
		cout << "in eol3: "<< endl;
		throw runtime_error(message.c_str());
	}
}

vector<string> month_input_tbl; 		// month_print_tbl[0]=="January
void init_input_tbl(vector<string>& tbl)
//initialize vector of output representations
{
	tbl.push_back("jan");
	tbl.push_back("feb");
	tbl.push_back("mar");
	tbl.push_back("apr");
	tbl.push_back("may");
	tbl.push_back("jun");
	tbl.push_back("jul");
	tbl.push_back("aug");
	tbl.push_back("sep");
	tbl.push_back("oct");
	tbl.push_back("nov");
	tbl.push_back("dec");
}
int month_to_int(string s)
// is s the name of a month? if so return its index [0:11] otherwise -1
{
	for (int i=0;i<12;i++) if(month_input_tbl[i]==s) return i;
	return -1;
}
bool is_valid(const Reading& r) {
	if(r.day < 1 || 31 < r.day) return false;
	if(r.hour < 1 || 23 < r.hour) return false;
	if(r.temp < implausible_min || implausible_max > r.temp) return false;
	return true;
}

void print(vector<string> s, ostream& os = cout) {
	for(auto a = s.begin();a != s.end();a++) {
		os<< *a << endl;
	}
}
void print(vector<Reading> s, ostream& os = cout) {
	for(auto a = s.begin();a != s.end();a++) {
		os<< "Hour " << a->hour << ": " << a->temp << " degrees." << endl;
	}
}

	


void print_year(ostream& os, const Year& y) {
	os << y.year << endl;
}


int main() {
	init_input_tbl(month_input_tbl);
	string filename = "temp_data.txt";
	ifstream ifs(filename.c_str());
	if(!ifs) throw runtime_error("can't open input file");

	ifs.exceptions(ifs.exceptions() | ios_base::badbit);	// throw for bad()

	//open an output file:
	ofstream ofs("temp_output.txt");
	if(!ofs) throw runtime_error("can't open output file");

	// read an arbitrary # of years
	vector<Year> ys;
	while(true) {
		Year y;			// get a freshly initialized Year each time around
		if(!(ifs>>y)) break;
		ys.push_back(y);
	}
	cout << "read" << ys.size() << " years of readings" << endl;
	for(int i = 0; i<ys.size();++i) print_year(ofs, ys[i]);
}

