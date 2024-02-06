#include "../my_array.h"
#include "human.h"
#include "test.h"
#include <cstddef>
#include <exception>
#include <stdexcept>
#include <string>
using namespace std::literals;

using my::array;

void test_constructors() {
  my::array<int, 5> foo{0, 1, 2, 3, 4};
  my::array<int, 5> goo = {0, 1, 2, 3, 4};
  my::array<int, 5> hoo;
  my::array<Human, 50> ioo;

  assert(foo.size() == 5);
  assert_equal(goo.size(), static_cast<size_t>(5));
  assert_equal(hoo.size(), static_cast<size_t>(5));
  assert_equal(ioo.size(), static_cast<size_t>(50));
}
void test_move() {
  my::array<int, 5> foo{0, 1, 2, 3, 4};
  my::array<int, 5> goo{std::move(foo)};
  my::array<int, 5> hoo;
  assert_equal(goo[4], 4);
  assert_equal(foo.data(), static_cast<int *>(nullptr));
  hoo = std::move(foo); // foo already moved from
  assert_equal(hoo.data(), static_cast<int *>(nullptr));
}

void test_access() {
  my::array<int, 5> foo{0, 1, 2, 3, 4};
  assert_equal(foo.front(), 0);
  assert_equal(foo.back(), 4);
  assert_equal(foo.at(2), 2);
  assert_throw(std::out_of_range("hi"), [&]() { foo.at(7); });
  assert_equal(foo.at(2), 2);
}

void test_iterators() {
  my::array<int, 5> foo{0, 1, 2, 3, 4};
  assert_equal(*foo.begin(), 0);
  assert_equal(*++foo.begin(), 1); // sexy operator precedence!
  assert_equal(*--foo.end(), 4);

  assert_equal(*foo.rbegin(), 4, "rbegin");
  assert_equal(*++foo.rbegin(), 3, "rbegin");
  assert_equal(*--foo.rend(), 0, "rend");
}

void test_erase() {}

int main(int argc, char *argv[]) {
  test_constructors();
  test_access();
  test_iterators();
  test_move();

  test_results();
  return 0;
}
