//#include <temp.h>
#include "temp.h"
using namespace std;

istream& operator>>(istream& is, Reading& r)
// read a temperature reading from is into r
// format: ( 3 4 9.7)
// check format, but dont' bother with data validity
{
	cout << "in reading: ";
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
	cout << "in month: ";
	cout << m.month << endl;
	cout << m.day[0].hour[0] << endl;

	Reading r;
	int duplicates = 0;
	int invalids = 0;
	//cout << "r: ";
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
	cout << "in year: ";
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
	cout << yy << endl;
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

