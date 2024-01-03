#include <algorithm>
#include <iostream>
using std::cout;
using std::endl;
/* template<class T>  */
class vector {
  /* private: */
public:
  size_t sz;
  double *elem;

  double operator[](int i) { return elem[i]; }

  vector(size_t s) : sz{s}, elem{new double[s]} {};
  vector(std::initializer_list<double> lst);
  vector(const vector &arg);

  vector &operator=(const vector &);

  ~vector() { delete[] elem; };
};

void copy(double *from, int sz, double *to) {
  for (int i = 0; i < sz; ++i) {
    to[i] = from[i];
  }
}

void print_vector(const vector &v) {
  for (auto i = 0; i < v.sz; ++i) {
    std::cout << v.elem[i] << " ";
  }
  cout << endl;
}
