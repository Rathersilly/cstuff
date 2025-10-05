#include "include/test.h"
#include "insertion_sort.h"
#include "search.h"
#include <algorithm>
#include <functional>
#include <random>
#include <vector>
using namespace std;
std::mt19937 mt{std::random_device{}()};

vector<int> get_random_vector(
    size_t n, std::function<unsigned int()> fun = [] { return mt(); }) {

  vector<int> vec(n);
  std::generate(vec.begin(), vec.end(), [=] { return fun() % 10; });

  return vec;
}

void test_int_sort_random(const char *str = __builtin_FUNCTION()) {
  auto vec = get_random_vector(30, mt);
  insertion_sort(vec.begin(), vec.end());
  assert_sorted(vec.begin(), vec.end());
}
void test_int_sort_random_w_iterators(const char *str = __builtin_FUNCTION()) {
  auto vec = get_random_vector(30, mt);
  insertion_sort(vec);
  assert_sorted(vec.begin(), vec.end());
}
void test_int_sort_reverse(const char *str = __builtin_FUNCTION()) {
  auto vec = get_random_vector(30, mt);
  insertion_sort(vec.begin(), vec.end());
  assert_sorted(vec.begin(), vec.end());
}
void test_int_sort_greater(const char *str = __builtin_FUNCTION()) {
  auto vec = get_random_vector(30, mt);
  insertion_sort(vec.begin(), vec.end(), std::greater<>{});
  assert_sorted(vec.rbegin(), vec.rend());
}
void test_int_sort_evens_first(const char *str = __builtin_FUNCTION()) {
  auto vec = get_random_vector(30, mt);

  auto even_first_comparator = [](int a, int b) {
    return (a % 2 == b % 2 ? (a < b) : (a % 2 == 0));
  };

  insertion_sort(vec.begin(), vec.end(), even_first_comparator);
  assert(std::is_partitioned(vec.begin(), vec.end(),
                             [](int a) { return a % 2 == 0; }));
}

void test_short_insertion_sort(const char *str = __builtin_FUNCTION()) {
  auto vec = get_random_vector(30, mt);
  shortest_insertion_sort2(vec.begin(), vec.end());
  assert_sorted(vec.begin(), vec.end());
}
void test_linear_search(const char *str = __builtin_FUNCTION()) {

  vector<int> vec{1, 2, 3, 4, 5};

  auto it = linear_search(vec.begin(), vec.end(), 4);
  assert(*it == 4);
  it = linear_search(vec.begin(), vec.end(), 7);
  assert(it == vec.end());
}
int main(int argc, char *argv[]) {
  vector<int> v{1, 3, 5, 2, 4};
  print_vector(v);
  InsertionSort(v.begin(), v.end());
  print_vector(v);

  test_int_sort_random();
  test_int_sort_random_w_iterators();
  test_int_sort_reverse();
  test_int_sort_greater();
  test_int_sort_evens_first();
  test_short_insertion_sort();
  test_linear_search();

  test_results();
  return 0;
}
