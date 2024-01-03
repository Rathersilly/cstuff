#include "vector.h"

#define GREEN "\033[32m" /* Green */
#define RESET "\033[0m"
#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
/* using namespace std; */

// constructors
// copy constructor
vector::vector(const vector &arg) : sz(arg.sz), elem{new double[sz]} {
  copy(arg.elem, arg.sz, elem);
}
// list initialization
vector::vector(std::initializer_list<double> lst)
    : sz{lst.size()}, elem{new double[sz]} {
  std::copy(lst.begin(), lst.end(), elem);
}
// copy assignment
vector &vector::operator=(const vector &arg) {
  INFO;
  double *p = new double[arg.sz];
  copy(arg.elem, arg.sz, p);
  delete[] elem;
  elem = p;
  sz = arg.sz;
  return *this;
}

int main(int argc, char *argv[]) {
  vector v(4);
  vector a{1, 2, 3};
  print_vector(v);
  print_vector(a);
  vector b = a;
  print_vector(b);
  b.elem[1] = 7;
  print_vector(a);
  print_vector(b);
  a.elem[1] = 9;
  b = a;
  print_vector(a);
  print_vector(b);

  return 0;
}
