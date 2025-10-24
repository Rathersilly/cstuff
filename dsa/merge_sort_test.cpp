// g++ -std=c++20 foo.cpp -lCatch2Main -lCatch2

#include "merge_sort.h"

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

TEST_CASE("Merge two sorted vectors", "[merge]") {

  std::vector<int> a = {1, 3, 5, 7};
  std::vector<int> b = {2, 4, 6, 8};

  std::vector<int> c = {0};
  std::vector<int> d = {1, 2};

  std::vector<int> result = merge(a, b);
  CHECK(ranges::is_sorted(result));
  CHECK(result.size() == a.size() + b.size());

  for (int i = 0; i < 10; ++i) {
    std::vector<int> a;
    std::vector<int> b;
    a.reserve(200);
    b.reserve(200);
    std::generate(a.begin(), a.end(), rdigit);
    std::generate(b.begin(), b.end(), rdigit);
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    auto c = merge(a, b);
    CHECK(is_sorted(c.begin(), c.end()));
  }

  auto rd_increment = [count = 0]() mutable { return count += mt() % 10; };
  for (int i = 0; i < 10; ++i) {

    std::vector<int> r1(10);
    std::vector<int> r2(10);
    std::generate(r1.begin(), r1.end(), rd_increment);
    std::generate(r2.begin(), r2.end(), rd_increment);
    result = merge(r1, r2);
    CHECK(ranges::is_sorted(result));
    CHECK(result.size() == r1.size() + r2.size());
  }
}

TEST_CASE("merge_sort", "[merge_sort]") {

  std::vector<int> a = {1, 3, 2, 5, 4, 7};
  auto b = merge_sort(a);
  // print("{}", a);
  CHECK(ranges::is_sorted(b));
}

TEST_CASE("merge_sort_inplace", "[merge_sort]") {

  std::vector<int> a(20);
  std::generate(a.begin(), a.end(), rdigit);
  // fmt::print("{}", a);
  merge_sort_inplace(a);
  // print("{}", a);
  CHECK(ranges::is_sorted(a));
}

TEST_CASE("merge sort benchmark", "[!benchmark]") {
  std::vector<int> a(20);
  std::generate(a.begin(), a.end(), rdigit);
  auto b = a;

  BENCHMARK("Naive Merge Sort") { return merge_sort(a); };
  BENCHMARK("In Place Merge Sort") { return merge_sort_inplace(b); };
}

TEST_CASE("Merge Sort with Insertion Sort(for small n)", "[insertion_sort]") {

  SECTION("Small Array only uses insertion_sort") {

    vector<int> arr;
    generate_n(back_inserter(arr), 5, rdigit);
    print("sorted: {}\n", arr);
    auto sorted_arr = merge_and_insertion_sort(arr);
    print("sorted: {}\n", sorted_arr);
    CHECK(std::is_sorted(sorted_arr.begin(), sorted_arr.end()));
    CHECK(arr.size() == sorted_arr.size());
    CHECK(
        std::is_permutation(sorted_arr.begin(), sorted_arr.end(), arr.begin()));
  }

  vector<int> arr;
  generate_n(back_inserter(arr), 30, rdigit);
  print("array: {}\n", arr);

  auto sorted_arr = merge_and_insertion_sort(arr);
  print("sorted: {}\n", sorted_arr);
  print_v(sorted_arr);

  CHECK(std::is_sorted(sorted_arr.begin(), sorted_arr.end()));
  CHECK(arr.size() == sorted_arr.size());
  CHECK(std::is_permutation(sorted_arr.begin(), sorted_arr.end(), arr.begin()));
}
