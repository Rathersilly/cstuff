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

// ppp ch19 drills

template<class T>
struct S {
	S(T t) : val(t) {}

	T& get();
	const T cget(); 		// cant overload get with just return type
	const T get() const;	// but can with const function
	void set(T);
	void operator=(T t);
	
	private:
	T val;
};

template<class T>
T& S<T>::get() { return val; }

template<class T>
const T S<T>::get() const { return val; }

template<class T>
const T S<T>::cget() { return val; }


template<class T>
void S<T>::set(const T t)
{
	val = t;
}

template<class T>
void S<T>::operator=(const T t)
{
	val = t;
}

template<class T>
std::ostream& operator<<(std::ostream& os, S<T>& t)
{
	os << t.get();
	return os;
}

template<class T>
void read_val(T& v)
{
	cin >> v;
}

int main() {
	S<int> s{1};
	S<char> c{'x'};
	S<double> d{5.51};
	S<string> x{"hello"};


	cout << s << endl;
	cout << c << endl;
	cout << d << endl;
	cout << x << endl;

	x.set("sup");
	cout << x << endl;
	
	x = "hey there";
	x = "hey there";
	cout << x << endl;

	read_val<int>(s.get());
	cout << s << endl;
}


