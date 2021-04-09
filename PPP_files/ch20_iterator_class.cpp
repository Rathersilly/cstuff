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

// ppp ch20 iterator class
// not sure if operators are sending the appropriate response eg lvalue/rvalue
// also should probably throw some errors somewhere

template<typename T>
class Iterator {
	public:
		T* elem;
		Iterator(T* t) : elem(t) {};
		Iterator() {elem = nullptr;}
		bool operator==(Iterator<T> i) { return elem == i.elem;}
		bool operator!=(Iterator<T> i) { return elem != i.elem;}

		// operator overloading:
		// https://docs.microsoft.com/en-us/cpp/cpp/increment-and-decrement-operator-overloading-cpp?view=msvc-160
		Iterator& operator++() {
			// same thing:
			// elem += sizeof(T);
			elem++;	
			return *this;
		}
		Iterator& operator--() {
			//elem -= sizeof(T);
			elem--;	
			return *this;
		}
		// I don't currently see a reason to implement postfix incrememt
		// Iterator operator++(int) {}

		T& operator=(T& val) {
			*elem = val;
			return *elem;
		}
		T operator=(Iterator<T> i) {
			return *i.elem;
		}
		T& operator*() {
			return *elem;
		}




};
//template<typename T>


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


	Iterator<int> ai {a};
	cout << a << endl;
	// these are the same
	// member access (. or ->) has higher precedence than dereference (*)
	cout << ai.elem << " " << *(ai.elem) << endl;
	cout << ai.elem << " " << *ai.elem << endl;

	//ai++;
	cout << ai.elem << " " << *ai.elem << endl;
	++ai;
	cout << ai.elem << " " << *ai.elem << endl;

	// testing assignment operators
	int x = 0;
	x = *ai;
	cout << x << endl;
	*ai = 5;
	cout << *ai << endl;
	Iterator<int> first = a;
	Iterator<int> last = a + 3;
	for(Iterator<int> i = first;i != last;++i) {
		cout << GREEN << *i << endl;
	}

}

