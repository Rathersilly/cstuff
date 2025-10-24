#include "../test/test.h"
#include "selection_sort.h"
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

void print_vector(const vector<int> vec, string msg = "") {
  cout << msg;
  // copy(vec.begin(), vec.end(), ostream_iterator<int>(std::cout, " "));

  for_each(vec.begin(), vec.end(), [](const int &n) { cout << n << " "; });
  cout << endl;
}

void test_sel_sort_random(const char *str = __builtin_FUNCTION()) {
  auto vec = get_random_vector(30, mt);
  selection_sort(vec.begin(), vec.end());
  assert_sorted(vec.begin(), vec.end());
}
void test_sel_sort_random_w_iterators(const char *str = __builtin_FUNCTION()) {
  auto vec = get_random_vector(30, mt);
  selection_sort(vec.begin(), vec.end());
  assert_sorted(vec.begin(), vec.end());
}
void test_sel_sort_reverse(const char *str = __builtin_FUNCTION()) {
  auto vec = get_random_vector(30, mt);
  selection_sort(vec.begin(), vec.end());
  assert_sorted(vec.begin(), vec.end());
}
void test_sel_sort_greater(const char *str = __builtin_FUNCTION()) {
  auto vec = get_random_vector(30, mt);
  selection_sort(vec.begin(), vec.end(), std::greater<>{});
  assert_sorted(vec.rbegin(), vec.rend());
}
void test_sel_sort_evens_first(const char *str = __builtin_FUNCTION()) {
  auto vec = get_random_vector(30, mt);

  auto even_first_comparator = [](int a, int b) {
    return (a % 2 == b % 2 ? (a < b) : (a % 2 == 0));
  };

  selection_sort(vec.begin(), vec.end(), even_first_comparator);
  assert(std::is_partitioned(vec.begin(), vec.end(),
                             [](int a) { return a % 2 == 0; }));
}

void test_shortest_selection_sort(const char *str = __builtin_FUNCTION()) {
  auto vec = get_random_vector(30, mt);
  shortest_selection_sort(vec.begin(), vec.end());
  assert_sorted(vec.begin(), vec.end());
}

int main(int argc, char *argv[]) {

  test_sel_sort_random();
  test_sel_sort_random_w_iterators();
  test_sel_sort_reverse();
  test_sel_sort_greater();
  test_sel_sort_evens_first();
  test_shortest_selection_sort();
  test_results();
  return 0;
}
