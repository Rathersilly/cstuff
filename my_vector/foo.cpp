#include "my_vector.h"
#include "ruby_vector.h"
#include <cassert>

void test_subscript() {
  rubyVector<int> a;
  cout << a.size() << endl;
  myVector<int> v{1, 2, 3, 4, 5};
  rubyVector<int> r{1, 2, 3, 4, 5};
  assert(r[-1] == 5);
  cout << r[-2];
}
int main(int argc, char *argv[]) { return 0; }
