// g++ -std=c++20 foo.cpp -lCatch2Main -lCatch2
#include "counting_radix_bucket_sorts.h"

#include <algorithm>
#include <iterator>
#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>

#include <fmt/base.h> // NOTE: link -lfmt
#include <fmt/ranges.h>
#include <random>

std::mt19937 mt{std::random_device{}()};
std::uniform_int_distribution<int> int_range(0, 9);
int rdigit() { return int_range(mt); }

void print_v(const vector<int> vec) {

  for_each(vec.begin(), vec.end(), [](const int &n) { printf("%d ", n); });
  printf("\n");
}

TEST_CASE("Counting Sort", "[counting]") {

  vector<int> v(10);
  std::iota(v.begin(), v.end(), 0);
  std::shuffle(v.begin(), v.end(), mt);

  vector<int> v2(20);
  std::generate(v2.begin(), v2.end(), [] { return mt() % 10; });

  counting_sort(v);
  CHECK(1 == 1);
  CHECK(ranges::is_sorted(v));

  counting_sort(v2);
  CHECK(ranges::is_sorted(v2));
  // CHECK(v2.size() == v.size());
}
TEST_CASE("Radix Sort", "[radix]") {
  vector<int> v2(20);
  std::generate(v2.begin(), v2.end(), [] { return mt() % 1000; });
  print("{}\n", v2);
  radix_sort(v2);
  print("{}\n", v2);
}
