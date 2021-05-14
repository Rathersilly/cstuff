#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <functional>		// std::function
//#include <map>		// std::function
using namespace std;

template<typename T>
class vector {
	public:
		using size_type = long unsigned int;
		size_type sz;
		T* elem;
		// space is index one past end of allocated space
		size_type space;

		vector() {sz = 0; elem = nullptr;}
		vector(initializer_list<T> lst)
			: sz{lst.size()}, elem{new T[sz]}
		{
			copy(lst.begin(),lst.end(),elem);
		}
		vector(int size) : sz(size), elem{new T[size]} {}

		// copy constructor && copy assignment
		vector(const vector&);
		vector& operator=(const vector&);

		// move constructor && move assignment
		vector(vector&&);
		vector& operator=(vector&&);

		~vector() { delete[] elem; }

		T& operator[](int n) { return elem[n]; }
		T operator[](int n) const { return elem[n]; };
	private:

		void reserve(int newalloc)
		{
			if (newalloc <= sz) return;
			T* tmp = new T[newalloc];
			for(int i = 0;i < sz;++i) {
				tmp[i] = elem[i];
			}
			delete[] elem;
			elem = tmp;
			space = newalloc;
		}
		void push_back(T item)
		{
			if (sz == space) { 
				space == 1 ? reserve(8) : reserve(2*space);
			}
			elem[sz] = item;
			++sz;
		}

			




};
/*
template<typename T>
T& vector<T>::operator[](int n)
{
	return elem[n];
}

template<typename T>
T vector<T>::operator[](int n)
{
	return elem[n];
}
*/

int main()
{


	vector<int> a;
	vector<int> b {1,2,3};
	vector<int> c(10);

	cout << b[0];
}
