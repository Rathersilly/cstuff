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

TEST_CASE("Insertion Sort with std::vector", "[vector]") {
  int size = 40;
  vector<int> vec;
  generate_n(back_inserter(vec), size, [] { return mt() % 10; });
  // print("{}\n", vec);

  SECTION("insertion_sort with bidir iterator") {
    print("insertion_sort with bidir iterator\n");
    auto sorted_vec = vec;
    insertion_sort(sorted_vec.begin(), sorted_vec.end());
    print("{}\n", sorted_vec);
    CHECK(std::is_sorted(sorted_vec.begin(), sorted_vec.end()));
    CHECK(std::is_permutation(sorted_vec.begin(), sorted_vec.end(), vec.begin(),
                              vec.end()));
    // for (auto it = sorted_vec.begin(); it != sorted_vec.end(); ++it) {
    //   print("{:2} ", *it);
    // }
    // print("\n");
  }

  SECTION("insertion_sort with 2 for loops") {
    print("insertion_sort with 2 for loops\n");

    print("{}\n", vec);
    auto sorted_vec = vec;
    insertion_sort_2fors(sorted_vec.begin(), sorted_vec.end());
    // for (auto it = sorted_vec.begin(); it != sorted_vec.end(); ++it) {
    //   print("{:2} ", *it);
    // }
    // print("\n");
    CHECK(std::is_sorted(sorted_vec.begin(), sorted_vec.end()));
    CHECK(std::is_permutation(sorted_vec.begin(), sorted_vec.end(), vec.begin(),
                              vec.end()));
  }
}
TEST_CASE("Insertion Sort with std::list", "[list]") {
  int size = 40;
  std::vector<int> vec;
  std::generate_n(back_inserter(vec), size, [i = 0]() mutable { return i++; });
  std::shuffle(vec.begin(), vec.end(), mt);

  std::list<int> list;
  std::copy(vec.begin(), vec.end(), back_inserter(list));

  for (auto it = list.begin(); it != list.end(); ++it) {
    print("{:2} ", *it);
  }
  print("\n");

  SECTION("insertion_sort with bidir iterator") {

    insertion_sort(list.begin(), list.end());
    for (auto it = list.begin(); it != list.end(); ++it) {
      print("{:2} ", *it);
    }
    print("\n");

    CHECK(std::is_sorted(list.begin(), list.end()));
    CHECK(
        std::is_permutation(list.begin(), list.end(), vec.begin(), vec.end()));
  }
  // SECTION("insertion_sort with 2 for loops") {
  //
  //   insertion_sort_2fors(list.begin(), list.end());
  //   for (auto it = list.begin(); it != list.end(); ++it) {
  //     print("{:2} ", *it);
  //   }
  //   print("\n");
  //
  //   CHECK(std::is_sorted(list.begin(), list.end()));
  //   CHECK(
  //       std::is_permutation(list.begin(), list.end(), vec.begin(),
  //       vec.end()));
  // }
}
