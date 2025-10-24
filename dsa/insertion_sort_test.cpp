// #include "insertion_sort.h"

#include "insertion_sort.h"
#include <algorithm>
#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <iterator>
#include <list>
#include <random>
#include <vector>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>

using namespace std;
using namespace fmt;
std::mt19937 mt{std::random_device{}()};
std::uniform_int_distribution<> die2{0, 1};

TEST_CASE("Insertion Sort") {
  vector<int> arr;
  generate_n(back_inserter(arr), 10, [] { return mt() % 10; });
  print("{}\n", arr);
  insertion_sort(arr);
  print("{}\n", arr);
  CHECK(std::is_sorted(arr.begin(), arr.end()));
}
TEST_CASE("Insertion Sort with std::list") {
  int num = 10;
  std::vector<int> vec;
  for (int i = 0; i < num; ++i) {
    vec.push_back(i);
  }
  std::list<int> list;
  std::copy(vec.begin(), vec.end(), back_inserter(list));
  print("{}\n", list);
  insertion_sort(list.begin(), list.end());
  // print("{}", list);
}
