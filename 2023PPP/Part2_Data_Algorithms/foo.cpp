#include "vector.h"

#define GREEN "\033[32m" /* Green */
#define RESET "\033[0m"
#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
int main(int argc, char *argv[]) {
  vector<int> m(10);
  vector<int> v(4);
  vector<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  print_vector<int>(v);
  print_vector<int>(a);
  vector<int> b = a;
  print_vector<int>(b);
  b[1] = 7;
  print_vector<int>(a);
  print_vector<int>(b);
  a[1] = 9;
  b = a;
  print_vector<int>(a);
  print_vector<int>(b);
  vector<int> *c = new vector<int>;
  delete c;
  std::cout << v[1];
  v[1] = 12;
  std::cout << v[1];
  const vector<int> d{1, 2, 3};
  int e = d[2];
  cout << a.size() << endl;
  cout << a.capacity() << endl;
  a.reserve(20);
  cout << a.size() << endl;
  cout << a.capacity() << endl;
  cout << a.capacity() << endl;
  a.resize(3);
  print_vector<int>(a);
  a.push_back(23);
  print_vector<int>(a);

  return 0;
}
