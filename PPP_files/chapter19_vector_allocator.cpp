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
using namespace std;

// ch 19 vector class part 2 - allocator
// NOTE: stl vector provides ranged checked at() and unchecked operator[]()
//
// NOTE: construct and destroy are deprecated in c++17 and will be removed in c++ 20
// look up allocator_traits for info
//
// an obj of the allocator class does 4 things:

// allocate memory of size suitable to hold a T obj (without initializing)
// construct an obj of type T in that uninitialized space
// destroy an obj of type T, returning its space to the uninitialized state
// deallocate memory of size suitable to hold a T obj
//
// https://medium.com/@vgasparyan1995/what-is-an-allocator-c8df15a93ed
// "an allocator is a handle to a heap"
//
// T* allocate(size_t n);
// 		// allocates enough storage to store n instances
// 		
// 		// and returns a pointer to it
//
// void deallocate(T* p, size_t n);
// 		// releases the storage								
//
// void construct(T* p, Args ... args);
// 		// constructs an object with args parameters where p points to
//
// 	void destroy(T* p);
// 		// calls the destructor of the object where p points to
//
// allocator#allocate differs from new in that 

struct Range_error : out_of_range {
	// add an index that we can inspect 
	int index;
	Range_error(int i) : out_of_range{"Range error"},index(i){}
};

template<typename T, typename A = allocator<T>>
class vector {
	A alloc; 					// use allocate to handle memory for elements
	int sz;
	T* elem; 					
	int space;
public:
	vector() {INFO sz = 0;elem=nullptr;} 		// default constructor
	vector(int s) :sz(s), elem{new T[s]} {INFO}
	vector(initializer_list<T> lst)	// constructor from args
		:sz{lst.size()},elem{new T[sz]}
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

	T at(int n)
	{INFO
		cout << n << " " << sz << endl;
		//if(n<0||n>sz) throw out_of_range("hi");
		if(n<0||n>sz) throw Range_error{n};
		return elem[n];
	}
	void set(int n,T v)
	{INFO
		if(n<0||n>sz) throw out_of_range("hi");
		elem[n] = v;
	}
	T& operator[](int n)
	{INFO
		return elem[n];
	}
	T operator[](int n) const
	{INFO
		return elem[n];
	}
	void print();

	// outside class def, this function def would be:
	// template<typename T, typename A>
	// void vector<T,A>::reserve(int newalloc)
	void reserve(int newalloc)
	{
		if(newalloc<=space) return; 				// never decrease allocation
		//T* p = new T[newalloc];					// allocate new space
		T* p = alloc.allocate(newalloc);			// allocate new space
		//for(int i=0;i<sz;++i) { p[i] = elem[i];}
		for(int i=0;i<sz;++i) {alloc.construct(&p[i],elem[i]);}		// copy
		for(int i=0;i<sz;++i) {alloc.destroy(&elem[i]);}			// destroy
		//delete[] elem;
		alloc.deallocate(elem,space);				// deallocate old space
		elem = p;
		space = newalloc;
	}

	void resize(int newsize, T val = T())
		// make the vector have newsize elements
		// initialze each new element with the default value 0.0
	{
		reserve(newsize);
		//for(int i=sz;i<newsize;++i) elem[i] = 0; 		// before 2nd arg was added
		//for(int i=sz;i<newsize;++i) elem[i] = def;	// before allocator was used
		for(int i=sz;i<newsize;++i) alloc.construct(&elem[i],val); 	// construct
		for(int i=sz;i<newsize;++i) alloc.destroy(&elem[i]); 	// destroy
		sz = newsize;
	}

	void push_back(const T* val)
		// increase vector size by one; initialize the new element with d
	{
		if(space==0) {reserve(8);}					// start with space for 8 elements
		else if (sz==space) {reserve(2*space);}		// get more space	
		//elem[sz] = d;								
		alloc.construct(&elem[sz],val);				// add val at end
		++sz;										// increase the size
	}

};

//template<typename T>//, typename A>// = allocator<T>>
template<typename T, typename A>
vector<T,A>::vector(const vector<T,A>& arg)				// copy constructor
	// allocate elements,
	// then initialize them by copying
	:sz{arg.sz},elem{new T[arg.sz]}
{INFO
	copy(arg.elem,&arg.elem[sz],elem); 	//std::copy()
}

template<typename T, typename A>
vector<T,A>& vector<T,A>::operator=(const vector& a) 		// copy assignment
	// make this vector a copy of a
{INFO
	if (this==&a) return *this;			// self-assignment, no work needed
	if (a.sz<=space) {					// enough space, no need for allocation
		for(int i=0;i<a.sz;++i) elem[i] = a.elem[i];
		sz = a.sz;
		return *this;
	}
	T* p = new T[a.sz];
	copy(a.elem,&a.elem[sz],p);
	delete[] elem;
	space = sz = a.sz;
	elem = p;
	return *this;
}

template<typename T, typename A>
vector<T,A>::vector(vector&& a)				// move constructor
	:sz{a.sz},elem{a.elem} 				
{INFO
	a.sz = 0;							// make a an empty vector
	a.elem = nullptr;					// (it will be destructed soon probs)
}

template<typename T, typename A>
vector<T,A>& vector<T,A>::operator=(vector&& a) 	// move assignment
{ INFO
	delete[] elem;						// deallocate old space
	elem = a.elem;						// copy a's elem and sz
	sz = a.sz;
	a.elem = nullptr;					// make a the empty vector
	a.sz = 0;
	return *this;						// return a self-reference
}

template<typename T, typename A>
void vector<T,A>::print()
{
	for(int i=0;i<sz;++i) {
		cout << setw(4) << elem[i];
	}
	cout << endl;
}

template<typename T>
vector<T> letsmove()
{ INFO
	vector<T> res{1,2,3,4,5};
	return res;
}

int main() {

	vector<double> v1(4);

	try{v1.set(4,5.5);}catch(...){}
	cout << GREEN << "at and set" << RESET << endl;
	//cout << v1.at(4) << endl;
	cout << v1.at(3) << endl;
	cout << v1.at(2) << endl;
	cout << v1[3] << endl;
	cout << v1[2] << endl;
	cout << v1[6] << endl;
	try { cout << v1.at(10) << endl;}
	catch (Range_error& e) {cout << RED <<  e.what() << ", index:  " << e.index << RESET << endl;}

	// these 2 seem equal? ya it seems optional - S18.2
	//vector<double> v2 = {1.2,4.7,8.8, 10.5,44.4};
	cout << GREEN << "list initialization" << RESET << endl;
	vector<double> v2 {1.2,4.7,8.8, 10.5,44.4};
	cout << v2.at(4) << endl;
	cout << v2.at(3) << endl;
	cout << v2.at(2) << endl;

	cout << GREEN << "copy constructor" << RESET << endl;
	vector<double> v3 = v2;
	// equivalent to vector<double> v3 {v2};
	cout << v3.at(4) << endl;
	v2.set(4,99.9);
	cout << v2.at(4) << endl;
	cout << v3.at(4) << endl;

	cout << GREEN << "copy assignment" << RESET << endl;
	v2 = v1;
	cout << v1.at(4) << endl;
	cout << v2.at(4) << endl;

	v2.set(4,99.9);
	cout << v1.at(4) << endl;
	cout << v2.at(4) << endl;

	cout << GREEN << "move constructor" << RESET << endl;
	vector<double> v4 = letsmove<double>();
	v4[3] = 9.3;
	cout << v4[1] << " " <<v4[3] << endl;

	cout << GREEN << "move assignment" << RESET << endl;

	v2 = letsmove<double>();
	cout << v2.at(4) << endl;

	cout << GREEN << "copy constructor (now with SPACE!)" << RESET << endl;
	v2 = v2;
	v2.print();


}
