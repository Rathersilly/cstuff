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
		Link<Elem>* first;
		Link<Elem>* last;
	public:
		class Iterator;
		List()
		{
			first = new Link<Elem>;
			last = first;
			first->prev = nullptr;
			first->succ = last;
			last->prev = first;
			last->succ = nullptr;
		}

		List(Elem* e)
		{
			first = new Link<Elem>;
			last = new Link<Elem>;
			first->prev = nullptr;
			first->succ = last;
			first->val = *e;
			last->prev = first;
			last->succ = nullptr;
			//last->val = 0;
		}

		Iterator begin() 
		{
			Iterator i;
			i.link = first;
			return i;
		}
		Iterator end()
		{
			Iterator i;
			i.link = last;
			return i;
		}

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
	public:
		Iterator() {};
		Link<Elem>* link;

		Iterator(Link<Elem>* l) : link(l) {};
		bool operator==(Iterator i) { return link == i.link;}
		bool operator!=(Iterator i) { return link != i.link;}
		Iterator& operator++() {
			link = link->succ;	
			return *this;
		}
		Iterator& operator--() {
			link = link->prev;	
			return *this;
		}

		Link<Elem>& operator=(Elem& val) {
			*link = val;
			return *link;
		}
		Link<Elem> operator=(Iterator i) {
			return *i.link;
		}
		Elem operator*() {
			return link->val;
		}

};

	template<typename Elem>
typename List<Elem>::Iterator List<Elem>::insert(Iterator p, const Elem& v)
{
	Iterator a = begin();
	while(a != p) {
		if( a == end()) {break;}
		++a;
	}
	Link<Elem>* new_link = new Link<Elem>;
	new_link->val = v;
	new_link->succ = a.succ;
	a->succ->prev = new_link;
	a->succ = new_link;
	new_link->prev = a;
	return a;
}

	template<typename Elem>
void List<Elem>::push_back(const Elem& v)
{
	Link<Elem>* new_end = new Link<Elem>;
	last->val = v;
	last->succ = new_end;
	cout << "pushback" << last->val << endl;
	new_end->prev =last;
	new_end->succ = nullptr;
	last = new_end;
}

	template<typename Elem>
void List<Elem>::push_front(const Elem& v)
{
	Link<Elem>* new_beg = new Link<Elem>;
	new_beg->val = v;
	new_beg->succ = first;
	first->prev = new_beg;
	first = new_beg;
	new_beg->prev = nullptr;
}

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
void print(List<int> l)
{
	for(auto a = l.begin();a!= l.end();++a) {
		cout << a.link->val << " ";
	}
	cout << endl;
}


int main()
{
	int a = 10;
	int b = 20;
	List<int> l {&a};
	print(l);
	cout << *l.begin() << endl;
	//cout << *l.first << endl;

	cout << endl << "test push_back and push_front" << endl;
	//for(int i=0;i<10;++i) {
	for(int i=0;i<12;++i) {
		l.push_back(i);
	}
	print(l);
	cout << endl << "test iteration" << endl;
	for(auto a = l.begin();a != l.end();++a) {
		cout << *a << " ";
	}
	l.push_front(66);

	cout << endl << "test iteration" << endl;
	for(auto a = l.begin();a != l.end();++a) {
		cout << *a<< " ";
	}

	cout << endl << "test empty list" << endl;
	List<int> m;
	for(auto a = m.begin();a != m.end();++a) {
		cout << *a<< " ";
	}
	cout << endl << "test backwards iteration" << endl;
	auto x = l.end();
	while(x != nullptr){
		cout << *x<< " ";
		--x;
	}




	cout << endl << "tests over" << endl;
	cout << endl;
	print(l);





}



