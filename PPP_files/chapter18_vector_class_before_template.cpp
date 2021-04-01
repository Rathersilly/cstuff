//#define INFO cout << '\t' << __PRETTY_FUNCTION__ << " - " << __FILE__ << " - "<< __DATE__ << endl;
#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#include <iostream>
#include <iomanip>				// setw()

#include <string>
#include <string.h>
using namespace std;

// ch 18 vector class
//
// 7 essential operations to consider:
//
// - constructors from one or more args
// - default constructor
// - copy constructor (copy object of same type)
// - copy assignment
// - move constructor
// - move assignment
// - destructor

class vector {
	int sz;
	double* elem; 					
	int space;
public:
	vector() {INFO sz = 0;elem=nullptr;} 		// default constructor
	vector(int s) :sz(s), elem{new double[s]} {INFO}
	vector(initializer_list<double> lst)	// constructor from args
		:sz{lst.size()},elem{new double[sz]}
	{INFO
		copy(lst.begin(),lst.end(),elem);
	}
	vector(const vector&);				// copy constructor
	vector& operator=(const vector&);	// copy assignment
	// && notation is "rvalue ref"
	// move functions work because
	// compiler knows the argument
	// is about to go out of scope
	vector(vector&&); 					// move constructor
	vector& operator=(vector&&);		// move assignment

	~vector() { INFO delete[] elem; }		// destructor

	int size() const {INFO return sz; }
	int capacity() const { return space;}

	double get(int n) {INFO return elem[n]; }
	double set(int n,double v) {INFO elem[n] = v;}
	double& operator[](int n) {INFO return elem[n];}
	double operator[](int n) const {INFO return elem[n];}
	void print();

	void reserve(int newalloc)
	{
		if(newalloc<=space) return;
		double* p = new double[newalloc];
		for(int i=0;i<sz;++i) { p[i] = elem[i];}
		delete[] elem;
		elem = p;
		space = newalloc;
	}

	void resize(int newsize)
		// make the vector have newsize elements
		// initialze each new element with the default value 0.0
	{
		reserve(newsize);
		for(int i=sz;i<newsize;++i) elem[i] = 0;
		sz = newsize;
	}

	void push_back(double d)
		// increase vector size by one; initialize the new element with d
	{
		if(space==0) {reserve(8);}
		else if (sz==space) {reserve(2*space);}		// double the space
		elem[sz] = d;								
		++sz;
	}

};

vector::vector(const vector& arg)				// copy constructor
	// allocate elements,
	// then initialize them by copying
	:sz{arg.sz},elem{new double[arg.sz]}
{INFO
	copy(arg.elem,&arg.elem[sz],elem); 	//std::copy()
}

vector& vector::operator=(const vector& a) 		// copy assignment
	// make this vector a copy of a
{INFO
	if (this==&a) return *this;			// self-assignment, no work needed
	if (a.sz<=space) {					// enough space, no need for allocation
		for(int i=0;i<a.sz;++i) elem[i] = a.elem[i];
		sz = a.sz;
		return *this;
	}
	double* p = new double[a.sz];
	copy(a.elem,&a.elem[sz],p);
	delete[] elem;
	space = sz = a.sz;
	elem = p;
	return *this;
}

vector::vector(vector&& a)				// move constructor
	:sz{a.sz},elem{a.elem} 				
{INFO
	a.sz = 0;							// make a an empty vector
	a.elem = nullptr;					// (it will be destructed soon probs)
}

vector& vector::operator=(vector&& a) 	// move assignment
{ INFO
	delete[] elem;						// deallocate old space
	elem = a.elem;						// copy a's elem and sz
	sz = a.sz;
	a.elem = nullptr;					// make a the empty vector
	a.sz = 0;
	return *this;						// return a self-reference
}

vector letsmove()
{ INFO
	vector res{1,2,3,4,5};
	return res;
}

void vector::print()
{
	for(int i=0;i<sz;++i) {
		cout << setw(4) << elem[i];
	}
	cout << endl;
}

int main() {

	vector v1{4};

	v1.set(4,5.5);
	cout << GREEN << "get and set" << RESET << endl;
	cout << v1.get(4) << endl;
	cout << v1.get(3) << endl;
	cout << v1.get(2) << endl;


	// these 2 seem equal? ya it seems optional - S18.2
	//vector v2 = {1.2,4.7,8.8, 10.5,44.4};
	cout << GREEN << "list initialization" << RESET << endl;
	vector v2 {1.2,4.7,8.8, 10.5,44.4};
	cout << v2.get(4) << endl;
	cout << v2.get(3) << endl;
	cout << v2.get(2) << endl;

	cout << GREEN << "copy constructor" << RESET << endl;
	vector v3 = v2;
	// equivalent to vector v3 {v2};
	cout << v3.get(4) << endl;
	v2.set(4,99.9);
	cout << v2.get(4) << endl;
	cout << v3.get(4) << endl;

	cout << GREEN << "copy assignment" << RESET << endl;
	v2 = v1;
	cout << v1.get(4) << endl;
	cout << v2.get(4) << endl;

	v2.set(4,99.9);
	cout << v1.get(4) << endl;
	cout << v2.get(4) << endl;

	cout << GREEN << "move constructor" << RESET << endl;
	vector v4 = letsmove();
	v4[3] = 9.3;
	cout << v4[1] << " " <<v4[3] << endl;

	cout << GREEN << "move assignment" << RESET << endl;

	v2 = letsmove();
	cout << v2.get(4) << endl;

	cout << GREEN << "copy constructor (now with SPACE!)" << RESET << endl;
	v2 = v2;
	v2.print();


}
