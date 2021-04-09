//#define INFO cout << '\t' << __PRETTY_FUNCTION__ << " - " << __FILE__ << " - "<< __DATE__ << endl;
#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#include <iostream>
#include <fstream>

#include <iomanip>				// setw()
#include <stdexcept>			// std::out_of_range()
#include <string>
#include <string.h>
#include <vector>
using namespace std;

// ppp ch20

template<typename T>
class Iterator {
public:
	T* elem;
	Iterator(T* t) : elem(t) {};
	Iterator() {elem = nullptr;




}

void copy(int* f1, int* e1, int* f2) {
	cout << e1 << endl;
	for(int* i = f1;i< e1;++i) {
		cout << GREEN << i << " " << *i << endl;
		*f2 = *i;
		f2++;
	}
	cout << RESET;
}
void print(int* a, int n) {
	cout << n;
	for(int i = 0;i<n;++i) {
		cout << i << " " <<a[i] << " " << endl;
	}
	cout << "HI";
	cout << endl;
}


int main() {

	//int a[3] = {1,2,3};
	int a[3] {1,2,3};
	int b[3];

	copy(a, a+3, b);

	print(b,3);


	Iterator<int> ai {a[0]};


}

