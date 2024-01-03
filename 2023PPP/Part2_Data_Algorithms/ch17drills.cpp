// PPP Ch17: Vector and Free Store

#include <array>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

// Drill 4
void print_array10(ostream &os, int *a) {
  for (int i = 0; i < 10; ++i) {
    os << a[i] << endl;
  }
}
// Drill 7
void print_array(ostream &os, int *a, int n) {
  for (int i = 0; i < n; ++i) {
    os << a[i] << endl;
  }
}
// Drill 10
template <class T> void print_vector(vector<T> v) {
  for (int i = 0; i < v.size(); ++i) {
    cout << v[i] << " ";
  }
  cout << endl;
}
void p(int a) { cout << a << endl; }
void p(const int *a) { cout << *a << endl; }

int main(int argc, char *argv[]) {
  // Drill 1
  int *a{new int[10]{1, 2, 3}};
  // Drill 2
  for (int i = 0; i < 10; ++i) {
    cout << a[i] << endl;
  }
  // Drill 3
  /* delete[] a; */

  // Drill 4
  ostream os{cout.rdbuf()};
  print_array10(os, a);
  // Drill 5/6/8
  int *b{new int[10]{}};
  for (int i = 0; i < 10; ++i) {
    b[i] = 100 + i;
  }
  print_array(cout, b, 10);
  delete[] a;
  delete[] b;

  // Drill 10 contd
  vector<int> v(10, {1});
  for (int i = 0; i < 10; ++i) {
    v[i] = 100 + i;
  }
  print_vector(v);
  int *foo = new int{7};
  p(*a);
}
