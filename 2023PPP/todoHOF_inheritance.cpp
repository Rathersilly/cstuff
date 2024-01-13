#include <typeinfo>
#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
#define RESET "\033[0m"
#define RED "\033[31m"    /* Red */
#define GREEN "\033[32m"  /* Green */
#define YELLOW "\033[33m" /* Yellow */
#define BLUE "\033[34m"   /* Blue */
#include <string>
// #include <string.h>
// #include <sstream>
// #include <fstream>
// #include <vector>
// #include <fstream>
#include <iomanip> // setprecision(n), setw
#include <iostream>
// #include <list>
// #include <cmath>
// #include "goo.h"
// #include <unistd.h>
// #include <climits>          /// INT_MAX
// #include <algorithm>
// #include <unistd.h> 		// usleep
#include <typeinfo> // for typeid(foo).name()
#include <vector>
// #include <stdlib.h> 		// srand, rand
// #include <typeinfo>			// typeid

using namespace std;
template <class T> void print_vector(vector<T> v) {
  for (int i = 0; i < v.size(); ++i) {
    cout << v[i] << " ";
  }
  cout << endl;
}

class Foo {
public:
  Foo() { cout << "Constructing Foo"; }
  void fun() { cout << "Foo fun"; }
};
class Goo : Foo {
public:
  Goo() { cout << "Constructing Goo"; }
  void fun() {
    cout << "Goo fun";
    Foo::fun();
  }
};
int main() {
  Goo g;
  g.fun();
  ;
}