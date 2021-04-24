#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include <string>
#include <cstring>
#include <array>
#include <algorithm>
#include <functional>		// std::function
using namespace std;

// PPP ch21 21.4.2 - Predicates on class members
// also with lambdas

struct Record {
	string name;
	// this is deliberately ugly
	char addr[24];
	Record(string s,char c[24]) : name(s){
		int i = 0;
		while(c[i]) {
			addr[i] = c[i];
			++i;
		}
	}
};

void print(vector<Record> vr)
{
	for(auto a = vr.begin();a!=vr.end();++a){
		cout << a->name << "\t" << a->addr << endl;
	}
}

struct Cmp_by_name {
	bool operator()(const Record& a, const Record& b) const
	{
		return a.name < b.name;
	}
};

struct Cmp_by_addr {
	bool operator()(const Record& a, const Record& b) const
	{
		// this wont work - have to use strncmp cuz char*
		// return a.addr < b.addr;
		return strncmp(a.addr,b.addr,24) < 0;
	}
};

int main()
{
	vector<Record> vr;
	vr.push_back(Record("carlos","321 main st"));
	vr.push_back(Record("alice","723 fake st"));
	vr.push_back(Record("bob","223 main st"));
	vr.push_back(Record("diana","156 main st"));

	print(vr);

	cout << endl << "sorting by address: " << endl;
	sort(vr.begin(),vr.end(),Cmp_by_addr());
	print(vr);

	cout << endl << "sorting by name: " << endl;
	sort(vr.begin(),vr.end(),Cmp_by_name());
	print(vr);

	cout << endl << "sorting by name (with lambda): " << endl;
	sort(vr.begin(),vr.end(),
			[](const Record& a, const Record& b)
			{ return a.name < b.name; }
		);
	print(vr);

	cout << endl << "sorting by address (with lambda) (implicit return type): " << endl;
	sort(vr.begin(),vr.end(),
			[](const Record& a, const Record& b)
			{ return strncmp(a.addr,b.addr,24) < 0; }
		);
	print(vr);

	cout << endl << "sorting by address (with lambda) (auto return type): " << endl;
	sort(vr.begin(),vr.end(),
			[](const Record& a, const Record& b) -> auto
			{ return strncmp(a.addr,b.addr,24) < 0; }
		);
	print(vr);

	// lol why does asdf get set to 1?
	auto asdf = []() -> int { return 5; };
	cout << asdf << endl;

	auto add = [](int a,int b) {return a+b;};
	cout << add(3,6) << endl;

	// has to be compiled with std=c++17 at least
	// or will require template args
	std::function add2 {[](int a,int b) {return a+b;}};
	cout << add2(3,6) << endl;
	cout << __cplusplus << endl;

	// https://www.learncpp.com/cpp-tutorial/introduction-to-lambdas-anonymous-functions/
	//   // A regular function pointer.
	//   // Only works with an empty capture clause.
	double (*addNumbers1)(double, double){
		[](double a, double b) {
			return (a + b);
		}
	};

	cout << addNumbers1(1, 2) << endl;
}



