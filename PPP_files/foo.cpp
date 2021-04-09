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

// ppp ch20 List class
template<class Elem>
struct Link {
	Link* prev;
	Link* succ;
	Elem val;
};


template<class Elem>
class List {
	public:
		class Iterator;
		Link<Elem>* first;
		Link<Elem>* last;
		List(Elem* e) {
			first = new Link<Elem>;
			last = new Link<Elem>;
			first->prev = nullptr;
			first->succ = last;
			first->val = *e;
			last->prev = first;
			last->succ = nullptr;
			last->val = 0;
		}



		Iterator begin();
		Iterator end();

		Iterator insert(Iterator p, const Elem& v);
		Iterator erase(Iterator p);

		void push_back(const Elem& v);
		void push_front(const Elem& v);
		void pop_front();
		void pop_back();

		Elem& front() { return *begin(); }
		Elem& back() { return *end().prev;}

};
template<class Elem>
class List<Elem>::Iterator {
};

/*
		Iterator insert(Iterator p, const Elem& v);
		Iterator erase(Iterator p);
		void push_back(const Elem& v);
		void push_front(const Elem& v);
		void pop_front();
		void pop_back();

		Elem& front();
		Elem& back();

		*/

int main()
{
	int a = 10;
	int b = 20;
	List<int> l {&a};
	//cout << *l.first << endl;





}



