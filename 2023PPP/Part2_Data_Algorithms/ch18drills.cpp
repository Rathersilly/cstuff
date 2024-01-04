// Ch 18 Drills completed
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <class T> void print_vector(vector<T> v) {
  for (int i = 0; i < v.size(); ++i) {
    cout << v[i] << " ";
  }
  cout << endl;
}

// Drill 1
int ga[3]{1, 2, 3};
vector<int> gv{1, 2, 3};

// Array Drill 2-3
void f(int a[], int s) {
  int la[3];
  for (int i = 0; i < 3; ++i) {
    la[i] = ga[i];
    cout << la[i] << ' ';
  }
  int *p = new int[s];
  for (int i = 0; i < s; ++i) {
    p[i] = a[i];
    cout << p[i] << ' ';
  }
  delete[] p;
}

// Vector Drill 2-3
void f(vector<int> v) {
  vector<int> lv(v.size());
  for (int i = 0; i < v.size(); ++i) {
    lv[i] = v[i];
  }
  vector<int> lv2 = v;
  print_vector(lv);
  print_vector(lv2);
}
int factorial(int n) {

  if (n == 1)
    return n;
  return n * factorial(n - 1);
}
int main(int argc, char *argv[]) {

  // Array Drill 4
  f(ga, 3);
  int aa[10];
  for (int i = 0; i < 10; ++i) {
    aa[i] = factorial(i + 1);
  };
  f(aa, 10);

  // Vector Drill 4
  f(gv);
  vector<int> vv(10);
  for (int i = 0; i < 10; ++i) {
    vv[i] = factorial(i + 1);
  };
  f(vv);

  return 0;
}
