#include "../Part2_Data_Algorithms/vector.h"
#include "human.h"
#include "test.h"
#include <exception>

using my::vector;

// in function args, __builtin_FUNCTION will return caller
// https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
// could keep passing it maybe
void test_insert(const char *str = __builtin_FUNCTION()) {
  my::vector<int> qwer = {1, 2, 3, 4, 5};
  qwer.insert(3, 7);
  assert_equal(7, qwer[3]);
  qwer.resize(3);
  try {
    // this is super erroneous
    /* qwer.insert(99, 10); */
  } catch (std::exception &e) {
    cout << YELLOW << "caught error: " << e.what() << RESET << endl;
  }
  cout << qwer.size() << endl;
  auto it = qwer.insert(3, 99);
  assert_equal(qwer[3], 99);
  assert_equal((int)qwer.size(), 4);
  // assert proper iterator is returned
  assert_equal(*it, 99);
}
void test_erase(const char *str = __builtin_FUNCTION()) {
  my::vector<int> qwer = {1, 2, 3, 4, 5};
  qwer.erase(3);
  my::print_vector(qwer);
  assert_equal(qwer[3], 5);
  assert_equal_containers(qwer, vector<int>{1, 2, 3, 5});
  assert_equal((int)qwer.size(), 4);
}
void test_emplace(const char *str = __builtin_FUNCTION()) {
  /* my::vector<Human> people; */
  /* people.emplace(new Human("bob")); */
  /* people.emplace(0, "bob"); */
  /* cout << "emplace"; */
  /* assert(people[0].name() == "bob"); */
}
void test_shrink_to_fit(const char *str = __builtin_FUNCTION()) {
  my::vector<int> qwer = {1, 2, 3, 4, 5};
  qwer.reserve(10);
  assert_equal((int)qwer.capacity(), 10);
  qwer.shrink_to_fit();
  assert_equal((int)qwer.capacity(), 5);
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

  vector<int> bb = a; // copy ctor
  assert_equal(bb[0], 1);

  bb = a; // copy assignment
  assert_equal(bb[2], 3);
}

int main(int argc, char *argv[]) {
  test_insert();
  test_constructors();
  test_erase();

  /* test_emplace(); */
  test_shrink_to_fit();
  test_results();
  return 0;
}
