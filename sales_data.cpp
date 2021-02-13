#include <iostream>
#include <string>
#include "string.h"
#include <typeinfo>
#include <vector>
using namespace std;

// Sales_data class from C++ Primer
class Sales_data {
	public: 
		// defines the default constructor as well as one that takes a string constant
		Sales_data(std::string s = "") : bookNo(s) { }
		Sales_data(std::string s =, unsigned cnt, double rev :
				bookNo(s), units_sold(cnt), revenue(rev * cnt) { }
		Sales_data(std::istream &is = std::cin) { read(is, *this); }
		

}


int main (int argc, char *argv[])
{

	




}
