#include "include/test.h"
#include "merge_sort.h"
#include "search.h"
#include <algorithm>
#include <color_macros.h>
#include <functional>
#include <iostream>
#include <random>
#include <vector>
using namespace std;
std::mt19937 mt{std::random_device{}()};

vector<int> get_random_vector(
    size_t n,
    std::function<unsigned int()> fun = []() -> unsigned int { return mt(); }) {

  vector<int> vec(n);
  // std::generate(vec.begin(), vec.end(), [=] { return fun() % 10; });
  // std::generate(vec.begin(), vec.end(), [=] { return fun() % 10; });
  std::generate(vec.begin(), vec.end(), [=] { return fun() % 10; });
  return vec;
}

void test_merge_sort_random(const char *str = __builtin_FUNCTION()) {
  auto vec = get_random_vector(30, mt);
  merge_sort(vec.begin(), vec.end());
  assert_sorted(vec.begin(), vec.end());
}
void test_merge_sort_random_w_iterators(
    const char *str = __builtin_FUNCTION()) {
  auto vec = get_random_vector(30, mt);
  merge_sort(vec.begin(), vec.end());
  assert_sorted(vec.begin(), vec.end());
}
void test_merge_sort_reverse(const char *str = __builtin_FUNCTION()) {
  auto vec = get_random_vector(30, mt);
  merge_sort(vec.begin(), vec.end());
  assert_sorted(vec.begin(), vec.end());
}
void test_merge_sort_greater(const char *str = __builtin_FUNCTION()) {
  auto vec = get_random_vector(30, mt);
  merge_sort(vec.begin(), vec.end(), std::greater<>{});
  assert_sorted(vec.rbegin(), vec.rend());
}
void test_merge_sort_evens_first(const char *str = __builtin_FUNCTION()) {
  auto vec = get_random_vector(30, mt);

  auto even_first_comparator = [](int a, int b) {
    return (a % 2 == b % 2 ? (a < b) : (a % 2 == 0));
  };

  merge_sort(vec.begin(), vec.end(), even_first_comparator);
  assert(std::is_partitioned(vec.begin(), vec.end(),
                             [](int a) { return a % 2 == 0; }));
}

void test_linear_search(const char *str = __builtin_FUNCTION()) {

  vector<int> vec{1, 2, 3, 4, 5};

  auto it = linear_search(vec.begin(), vec.end(), 4);
  assert(*it == 4);
  it = linear_search(vec.begin(), vec.end(), 7);
  assert(it == vec.end());
}
int main(int argc, char *argv[]) {
  // auto vec = get_random_vector(10, mt);
  // auto vec = get_random_vector(20, mt);
  // print_vector(vec);
  // // merge_sort(vec);
  // merge_sort(vec.begin(), vec.end());
  // print_vector(vec);

  vector<int> v{1, 3, 5, 2, 4};
  // vector<int> v{1, 3, 5, 2, 4, 0, 6, 7, 8, 9};
  print_vector(v);
  merge_sort(v);
  // merge_sort(v.begin(), v.end());
  // print_vector(v);

  // test_merge_sort_random();
  // test_merge_sort_random_w_iterators();
  // test_merge_sort_reverse();
  // test_merge_sort_greater();
  // test_merge_sort_evens_first();
  // test_results();
  return 0;
}
