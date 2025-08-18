#include "info.h"
#include <iostream>

using std::cout, std::endl;

namespace my {

class vector {
private:
  int sz;
  int *elem;

public:
  vector(int s) : sz{s} { INFO elem = new int[s]; }
  int &operator[](int i) { return elem[i]; }
  int &operator[](int i) const { return elem[i]; }

  int size() const { return sz; }

  ~vector() { INFO delete[] elem; }
};

void print(const vector &v) {
  for (int i = 0; i < v.size(); ++i) {
    cout << v[i] << " ";
  }
  cout << endl;
}
} // namespace my

using namespace my;

int main() {

  vector v(3);
  v[2] = 3;
  print(v);

  int *a = new int[]{1, 2, 3, 4, 5};

  std::vector<int> vec(10);
  cout << vec[3] << endl;
}
