// #include "insertion_sort.h"

#include "insertion_sort.h"
#include <algorithm>
#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
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
  print("{}", arr);
  insertion_sort(arr);
  print("{}", arr);
  CHECK(std::is_sorted(arr.begin(), arr.end()));
}
