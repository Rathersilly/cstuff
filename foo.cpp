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
using namespace std;

// Reading PPP ch 10 - iostreams

const int not_a_reading = -7777;		// less than absolute 0
const int not_a_month = -1;
const int implausible_min = -200;
const int implausible_max = 200;

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
struct Day {
	vector<double> hour;
	Day();
};

Day::Day() : hour(24) {
	for (int i = 0; i<hour.size(); ++i) {
		hour[i] = not_a_reading;
	}
}

struct Month {
	int month;
	vector<Day> day;
	Month() : month(not_a_month), day(32) {}
};

struct Year {
	int year;
	vector<Month> month;
	Year() : month(12) {}
};


struct Reading {
	int day;
	int hour;
	double temp;
	// Reading(int h, double t) :hour(h), temp(t) {}
};
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

istream& operator>>(istream& is, Reading& r)
// read a temperature reading from is into r
// format: ( 3 4 9.7)
// check format, but dont' bother with data validity
{
	char ch1;
	if (is>>ch1 && ch1!='(') {		// could it be a Reading?
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}

	char ch2;
	int d;
	int h;
	double t;
	is >> d >> h >> t >> ch2;
	if (!is || ch2!=')') throw runtime_error("bad reading");
	r.day = d;
	r.hour = h;
	r.temp = t;
	return is;
}
istream& operator>>(istream& is, Month& m)
// read a month from is into m
// format: { month feb .... }
{
	char ch = 0;
	if (is >> ch && ch!='{') {
		is.unget();
		is.clear(ios_base::failbit);		// we failed to read a month
		return is;
	}

	string month_marker;
	string mm;
	is >> month_marker >> mm;
	if (!is || month_marker!="month") throw runtime_error("bad start month");
	m.month = month_to_int(mm);
	cout << "in month" << endl;
	cout << m.month << endl;
	cout << m.day[0].hour[0] << endl;

	Reading r;
	int duplicates = 0;
	int invalids = 0;
		cout << "r: ";
	while (is >> r) {
			cout << r.day << " " << r.hour << endl;
			if (is_valid(r)) {
				if (m.day[r.day].hour[r.hour] != not_a_reading) {
					++duplicates;
				}
				m.day[r.day].hour[r.hour] = r.temp;
			}
			else
				++invalids;
	}
	cout << r.day << endl;
	//cout << m.day << endl;
	//if(invalids) throw runtime_error("invalid readings in a month");
	//if(duplicates) throw runtime_error("duplicate readings in a month");
	end_of_loop(is,'}',"bad end of month");
	return is;
}
istream& operator>>(istream& is, Year& y)
// read a year from is into y
// format: { year 1900 ...}
{
	char ch;
	is >> ch;
	if(ch!='{') {
		is.unget();
		is.clear(ios::failbit);
		return is;
	}

	string year_marker;
	int yy;
	is >> year_marker >> yy;
	if (!is || year_marker!="year") throw runtime_error("bad start of year");
	y.year = yy;

	while(true) {
		Month m; 		// get a clean m each time around;
		if(!(is>>m)) break;
		cout << "y" << m.month << endl;
		y.month[m.month] = m;
	}
	end_of_loop(is,'}',"bad end of year");
	return is;
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

