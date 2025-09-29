#include "my_vector.h"
#include "ruby_vector.h"
#include <algorithm>
#include <cassert>
#include <color_macros.h>
#include <iostream>
#include <vector>

void test_reserve() {
  myVector<int> v(10);
  assert(v.capacity() == 10);
  v.reserve(12);
  assert(v.capacity() == 12);
  v.resize(13);
  assert(v.capacity() == 13);
}
void test_push_back() {

  myVector<int> v(10);
  assert(v.size() == 10);
  assert(v.capacity() == 10);
  v.push_back(4);
  assert(v.size() == 11);
  assert(v.capacity() == 20);
}

template <typename T, typename A = allocator<T>>
void print_vector(const myVector<T> &v) {
  for (auto i = 0; i < v.size(); ++i) {
    std::cout << v[i] << " ";
  }
  cout << endl;
}
void test_copy() {
  TRACE_GREEN();
  myVector<int> v1{1, 2, 3};
  myVector<int> v2{v1};
  assert(v2[1] == 2);
  assert(v2[2] == 3);

  myVector<int> v3;
  v3 = v2;
  assert(v3[1] == 2);
  assert(v3[2] == 3);
}

myVector<int> move_vector() {
  myVector<int> v{1, 2, 3, 4};
  return v;
}

void test_move() {
  FTRACE_GREEN();
  myVector<int> v{move_vector()}; // should use move constructor but doesnt -
                                  // compiler thing?
  myVector<int> vv{std::move(move_vector())};
  assert(v[3] == 4);
  v = std::move(move_vector());
  assert(v[3] == 4);
}

void test_iterator() {
  myVector<int> v{1, 2, 3, 4, 5};
  vector<int> vv{1, 2, 3, 4, 5};
  assert(*vv.begin() == 1);

  assert(*v.begin() == 1);
  assert((*v.begin())++ == 1);
  assert((*++v.begin()) == 2);
  assert(*(v.end() - 1) == 5);
  assert(*(v.begin() + 2) == 3);
  assert(*(2 + v.begin()) == 3);
}
void test_input_iterator() {
  myVector<int> v(5);
  std::generate_n(v.begin(), 5, [i = 0]() mutable { return i++; });
  print_vector(v);
}

void test_back_inserter() {
  TRACE_GREEN();
  myVector<int> v{1, 2, 3, 4, 5};
  cout << v.size() << " " << v.capacity() << " " << endl;
  cout << v.size() << " " << v.capacity() << " " << endl;
  myVector<int>::myBackInserter ins(&v);
  for (int i = 6; i < 10; ++i) {
    cout << v.size() << " " << v.capacity() << endl;
    ins = i;
  }
  print_vector(v);
}

int main(int argc, char **argv) {
  // test_reserve();
  // test_push_back();
  // myVector<int> v{1, 2, 3};
  // print_vector<int>(v);
  // test_copy();
  // test_move();
  // test_iterator();
  // test_back_inserter();
  test_input_iterator();
}
