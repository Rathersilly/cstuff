
#include <algorithm>
#include <iterator>
#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>

#include "search.h"
#include <random>

std::mt19937 mt{std::random_device{}()};
std::uniform_int_distribution<int> int_range(0, 9);
int rdigit() { return int_range(mt); }

TEST_CASE("Linear Search") {
  std::vector<int> v{1, 2, 3, 4, 5};
  auto it = simple_linear_search(v.begin(), v.end(), 2);
  CHECK(*it == 2);
  it = simple_linear_search(v.begin(), v.end(), 12);
  CHECK(it == v.end());
}

TEST_CASE("Linear Search with Sentinel") {
  std::vector<int> v{1, 2, 3, 4, 5};
  auto it = linear_search_with_concept(v.begin(), v.end(), 2);
  CHECK(*it == 2);
  auto sentinel = v.begin() + 2;
  it = linear_search_with_concept(v.begin(), sentinel, 4);
  CHECK(it == sentinel);
  it = linear_search_with_concept(v.begin(), sentinel + 3, 4);
  CHECK(*it == 4);
}
TEST_CASE("Interpolation Search") {
  std::vector<int> arr{10, 12, 13, 16, 18, 19, 20, 21,
                       22, 23, 24, 33, 35, 42, 47};

  for (size_t i = 0; i < arr.size(); ++i) {
    auto index = interpolation_search(arr, arr[i]);
    CHECK(index == i);
  }
  auto index = interpolation_search(arr, 17);
  CHECK(index == -1);
  // std::vector<int> arr(20);
  // std::iota(arr.begin(), arr.end(), 0);
  // auto index = interpolation_search(arr, 12);
  // CHECK(index == 12);
  // index = interpolation_search(arr, 6);
  // CHECK(index == 6);
  // index = interpolation_search(arr, 13);
  // CHECK(index == 2);
  // index = interpolation_search(arr, 35);
  // CHECK(index == 12);
  // index = interpolation_search(arr, 47);
  // CHECK(index == 14);
}
