//#define INFO cout << '\t' << __PRETTY_FUNCTION__ << " - " << __FILE__ << " - "<< __DATE__ << endl;
#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#include <iostream>
#include <iomanip>				// setw()
#include <stdexcept>			// std::out_of_range()
#include <string>
#include <string.h>
#include <vector>
using namespace std;

// ppp ch19 ex

template<typename T>
vector<T> sum(vector<T> v1, vector<T> v2)
{
	vector<T>* smaller = nullptr;
	vector<T>* bigger = nullptr;
	if(v1.size() < v2.size()) {
		smaller = &v1;
		bigger = &v2;
	} else {
		smaller = &v2;
		bigger = &v1;
	}
	vector<T> memo(bigger->size());
	for (size_t i = 0; i<smaller->size();++i) {
		memo[i] = (*smaller)[i] + (*bigger)[i];
	}
	for(size_t i =  smaller->size();i<bigger->size();++i) {
		memo[i] = (*bigger)[i];
	}
	return memo;
}


template<typename T>
void print(vector<T> v) 
{
	int i = 0;
	for(auto a: v) {
		cout << a << " ";
		++i;
		if (i > 20) break;
	}
	cout << endl;
}


int main()
{
	vector<int> v1{1,2,3,4,5,6,7};
	vector<int> v2{1,2,3,4,5,6,7,8,9,10};
	vector<int> v3 = sum(v1,v2);
	cout << v3[4]<< endl;
	cout << v3[9]<< endl;
	for(auto a: v3) {
		cout << a << " ";
	}


}

