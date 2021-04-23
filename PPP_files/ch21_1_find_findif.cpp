#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
using namespace std;

// PPP ch21 up to 21.4.1 - An abstract view of function objects

template<typename In, typename T>
	// In is input iterator, T is value type
In myfind(In first, In last, const T& val)
{
	while(first != last && val != *first) ++first;
	return first;
}

// 21.3
template<typename In, typename Pred >
	// Pred is predicate function
In myfind_if(In first, In last, Pred pred)
{
	while(first != last && !pred(*first)) ++first;
	return first;
}

// 21.4
class Larger_than {
	int v;
	public:
	Larger_than(int vv) : v(vv) {}
	bool operator()(int x) const { return x > v; }
};

// 21.4.1 - a mechanism for a function to carry around a state
// compare to ruby closures
class F {
	S s;
	public:
	F(const S& ss) : s(ss) { /* establish initial state */ }
	T operator() (const S& ss) const
	{
		// do something with ss to s
		// return a value of type T ( T is often void, bool, or S)

	}

	const S& state() const { return s; }
	void reset(const S& ss) { s = ss; }
};

bool gt5(int x) {
	if(x > 5) { return true;}
	return false;
}





int main()
{
	vector<int> vi;
	for(int i = 0;i<10;++i) {
		vi.push_back(i);
	}
	cout << endl << "testing myfind: " << endl;
	auto x = myfind(vi.begin(),vi.end(),7);
	cout << *x << endl;
	for(auto a = x;a<vi.end();++a) { cout << *a; } 
	cout << endl << gt5(5) << endl;
	cout << gt5(7) << endl;

	cout << endl << "testing myfind_if: " << endl;
	x = myfind_if(vi.begin(),vi.end(),gt5);
	cout << *x << endl;
	for(auto a = x;a<vi.end();++a) { cout << *a; } 

	cout << endl << "testing Larger_than class: " << endl;
	x = myfind_if(vi.begin(),vi.end(),Larger_than(5));
	cout << *x << endl;
	for(auto a = x;a<vi.end();++a) { cout << *a; } 
	
	int z = 5;
	//F f(5);

}
