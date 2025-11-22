#include "my_vector.h"
#include "ruby_vector.h"
#include <color_macros.h>
#include <cstdio>
#include <initializer_list>
#include <iostream>
#include <new>
#include <vector>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
using namespace Catch::Matchers; // for StartsWith()

// TODO: this is only half done

// template <typename T> bool verify_pool_invariants(const ObjectPool<T> &pool)
// {
//   CHECK(
//   check_freelist_integrity(pool));
//   return pool.num_used() + pool.num_free() == pool.num_allocated();
// }
template <class T> void print_vector(const myVector<T> &vec) {
  for (auto &x : vec) {
    std::cout << x << " ";
  }
  std::cout << std::endl;
}

class Object {
  const char *b = "hi";
  int a = 0;
};
TEST_CASE("Minimal test", "[minimal]") {
  vector<int> arr{1, 2, 3, 4, 5};
  //
}

TEMPLATE_TEST_CASE("myVector Constructors", "[vector][constructor]", int, char,
                   Object /*, int */) {
  SECTION("Default Constructor") {
    myVector<TestType> v;
    CHECK(v.size() == 0);
    CHECK(v.capacity() == 0);
  }
  SECTION("Size Constructor default initializes") {

    myVector<int> v(18);
    CHECK(v.size() == 18);
    CHECK(v.capacity() == 18);
    CHECK(v[0] == 0);
  }
  SECTION("Initializer List Constructor") {

    myVector<int> v{0, 1, 2};
    // myVector<Object> v2{"sup",2};
    CHECK(v[0] == 0);
    CHECK(v[2] == 2);
    CHECK(v.size() == 3);
    CHECK(v.capacity() == 3);
  }
  SECTION("Copy Constructor") {

    myVector<TestType> v;
    CHECK(v.size() == 0);
    CHECK(v.capacity() == 0);
  }
  SECTION("Move Constructor") {
    myVector<TestType> v1;
    myVector<TestType> v2{};

    // CHECK(v.size() == 0);
    // CHECK(v.capacity() == 0);
  }
  SECTION(" Constructor") {}
}

TEST_CASE("Reserve and Resize ", "[reserve]") {

  myVector<int> v;
  myVector<int> v3{0, 1, 2};

  SECTION("initial size and capacity") {
    CHECK(v.size() == 0);
    CHECK(v.capacity() == 0);

    CHECK(v3.size() == 3);
    CHECK(v3.capacity() == 3);
  }

  SECTION("resizing smaller changes size but not capacity") {
    v3.resize(2);
    CHECK(v3[1] == 1);
    CHECK(v3.size() == 2);
    CHECK(v3.capacity() == 3);
  }

  SECTION("can only reserve larger") {
    auto it = v3.begin();
    v3.reserve(2);
    CHECK(v3[2] == 2);
    CHECK(v3.capacity() == 3);
    CHECK(v3.begin() == it);
  }

  SECTION("reserving will affect iterators but not elements") {
    auto it = v3.begin();
    v3.reserve(10);
    CHECK(v3.capacity() == 10);
    CHECK(v3[2] == 2);
    CHECK(v3.begin() != it);

    // is fine test but triggers valgrind
    // REQUIRE_THROWS_AS(v.reserve(10000000000), std::bad_alloc);
  }
}

TEST_CASE("push_back", "[push_back]") {

  myVector<int> v;
  myVector<int> v3{0, 1, 2};
  SECTION("push_back pushes back") {
    v.push_back(0);
    CHECK(v[0] == 0);
  }

  SECTION("push_back reserves when needed") {
    auto start_capacity = v.capacity();
    v.push_back(0);
    CHECK(v.capacity() == 1);
    start_capacity = v.capacity();
    v.push_back(0);
    CHECK(v.capacity() == start_capacity * v.reserve_factor());

    v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    start_capacity = v.capacity();
    v.push_back(10);
    CHECK(v.capacity() == start_capacity * v.reserve_factor());
  }
}

TEST_CASE("Back Inserter", "[back_inserter]") {
  myVector<int> v{0, 1, 2, 3, 4};
  myBackInserter<myVector<int>> ins(v);

  SECTION("myBackInserter back inserts") {
    ins = 5;
    CHECK(v[5] == 5);
    for (int i = 6; i < 10; ++i) {
      ins = i;
    }
    CHECK(v[9] == 9);
    std::generate_n(ins, 10, [n = 10]() mutable { return n++; });
    print_vector(v);
    CHECK(v[19] == 19);
  }

  SECTION("operator* is no op") {
    ins = 5;
    CHECK(v[5] == 5);
    *ins = 6;
    CHECK(v[6] == 6);
  }
  SECTION("operator++ is no op") {
    ++ins = 5;
    CHECK(v[5] == 5);
    ins++ = 6;
    CHECK(v[6] == 6);
  }
}

// TODO:from here down isn't finished
// TEST_CASE("Assignment") {
//   myVector<int> v1{1, 2, 3};
//   myVector<int> v2{v1};
//   assert(v2[1] == 2);
//   assert(v2[2] == 3);
//
//   myVector<int> v3;
//   v3 = v2;
//   assert(v3[1] == 2);
//   assert(v3[2] == 3);
// }
// void move_vector();
// TEST_CASE("Move") {}
//
// TEST_CASE("Input Iterator") {
//   myVector<int> v{1, 2, 3, 4, 5};
//   vector<int> vv{1, 2, 3, 4, 5};
//   assert(*vv.begin() == 1);
//
//   assert(*v.begin() == 1);
//   assert((*v.begin())++ == 1);
//   assert((*++v.begin()) == 2);
//   assert(*(v.end() - 1) == 5);
//   assert(*(v.begin() + 2) == 3);
//   assert(*(2 + v.begin()) == 3);
// }
//
// void test_input_iterator() {
//   myVector<int> v(5);
//   std::generate_n(v.begin(), 5, [i = 0]() mutable { return i++; });
// }
