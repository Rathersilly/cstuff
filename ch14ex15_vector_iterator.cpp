#include <string>
// #include <sstream>
#include <fstream>
#include <iomanip> // setprecision(n), setw
#include <iostream>
#include <vector>
// #include <list>
// #include <cmath>
// #include "goo.h"
// #include <unistd.h>
// #include <climits>          /// INT_MAX
// #include <algorithm>
using namespace std;

// ch14 ex15 - vector iterator

class Iterator {

protected:
  virtual double *next() = 0;
};
class Vector_iterator : public Iterator {
public:
  Vector_iterator(vector<double> vv) : v(vv) { i = 0; }

  double *next() {
    if (i >= v.size()) {
      return 0;
    } else {

      double *n = &v[i];
      ++i;
      return n;
    }
  }

  vector<double> v;
  vector<double>::size_type i;
};
int main() {
  vector<double> v{3, 5, 7, 9.6};
  Vector_iterator vi(v);

  for (int i = 0; i < 10; ++i) {
    double *n = vi.next();
    if (n)
      cout << n << " " << *n << endl;
  }
}
