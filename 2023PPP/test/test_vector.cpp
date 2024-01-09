#include "../Part2_Data_Algorithms/vector.h"
#include "test.h"
#include <exception>

using my::vector;

// in function args, __builtin_FUNCTION will return caller
// https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
// could keep passing it maybe
void test_insert(const char *str = __builtin_FUNCTION()) {
  my::vector<int> qwer = {1, 2, 3, 4, 5};
  qwer.insert(7, 3);
  assert_equal(qwer[3], 7);
  qwer.resize(3);
  try {
    // this is super erroneous
    /* qwer.insert(99, 10); */
  } catch (std::exception &e) {
    cout << YELLOW << "caught error: " << e.what() << RESET << endl;
  }
  cout << qwer.size() << endl;
  qwer.insert(99, 3);
  assert_equal(qwer[3], 99);
  assert_equal((int)qwer.size(), 4);
}
void test_constructors(const char *str = __builtin_FUNCTION()) {
  /* try { */
  my::vector<int> asdf; // default
  my::vector<int> v(4); // args
  assert_equal((int)v.size(), 4);
  my::vector<int> a{1, 2, 3}; // init list
  assert_equal(a[0], 1);
  assert_equal(a[1], 2);
  assert_equal(a[2], 3);

  my::vector<int> b(a); // copy constructor
  assert_equal_containers<vector<int>>(a, b);
  assert_equal_containers<vector<int>>(a, v);

  vector<int> bb = a; // copy ctor
  assert_equal(bb[0], 1);

  bb = a; // copy assignment
  assert_equal(bb[2], 3);
}

int main(int argc, char *argv[]) {
  test_insert();
  test_constructors();
  test_results();
  return 0;
}
