// PPP Ch17: Vector and Free Store

#include <array>
#include <cstring>
#include <iostream>
#include <numeric>
#include <utility>
#define GREEN "\033[32m" /* Green */
#define RESET "\033[0m"
using namespace std;

/* template<class T>  */
class vector {
  /* private: */
public:
  size_t sz;
  double *elem;

  vector(size_t s) : sz{s}, elem{new double[s]} {};
  vector(initializer_list<double> lst) : sz{lst.size()}, elem{new double[sz]} {
    copy(lst.begin(), lst.end(), elem);
  }

  ~vector() { delete[] elem; };
};
void print_vector(vector v) {
  for (auto i = 0; i < v.sz; ++i) {
    cout << v.elem[i] << " ";
  }
}

int main(int argc, char *argv[]) {
  vector v(4);
  vector a{1, 2, 3};
  print_vector(a);
  return 0;
}
