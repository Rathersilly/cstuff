#include <string>
#include <sstream>
#include <iostream>
//#include <fstream>
#include <vector>
#include <fstream>

const int not_a_reading = -7777;		// less than absolute 0
const int implausible_min = -200;
const int implausible_max = 200;
const int not_a_month = -1;
struct Day {
	std::vector<double> hour;
	Day();
};


struct Month {
	int month;
	std::vector<Day> day;
	Month();
};

struct Year {
	int year;
	std::vector<Month> month;
	Year();
};


struct Reading {
	int day;
	int hour;
	double temp;
	// Reading(int h, double t) :hour(h), temp(t) {}
};
int month_to_int(std::string s);
bool is_valid(const Reading& r);

std::istream& operator>>(std::istream& is, Reading& r);
std::istream& operator>>(std::istream& is, Month& m);
std::istream& operator>>(std::istream& is, Year& y);
void end_of_loop(std::istream& is, char term, const std::string& message);

