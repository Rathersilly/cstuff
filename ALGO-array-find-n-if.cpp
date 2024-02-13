// NOTE: Some array algorithms including find_n_if()
// https://www.geeksforgeeks.org/find-second-largest-element-array/
// TODO: maybe benchmark these?
#include "my_helpers.h"
#include <algorithm> // std::shuffle, sort
#include <array>
#include <functional>
#include <iostream>
#include <memory>
using namespace std;
using namespace my;

template <size_t N> int smallest_index(const array<int, N> arr) {
  int small_i = 0;
  for (int i = 1; i < N; ++i) {
    if (arr[i] < arr[small_i])
      small_i = i;
  }
  return small_i;
}

template <size_t N>
std::array<int, 3> find_3_largest(const array<int, N> &arr) {
  static_assert(N >= 3, "array must be at least size 3");
  array<int, 3> res;
  std::copy(arr.begin(), arr.begin() + 3, res.begin());
  if (arr.size() == 3)
    return res;

  // smallest of the 3 in the largest array
  int small_i = smallest_index(res);

  for (int i = 3; i < arr.size(); ++i) {
    if (arr[i] > res[small_i]) {
      res[small_i] = arr[i];
      small_i = smallest_index(res);
    }
  }
  return res;
}
template <size_t Result_size, size_t Array_size>
std::array<int, Result_size> find_n_largest(const array<int, Array_size> &arr) {
  static_assert(Array_size >= Result_size, "can't find n largest of < n");
  array<int, Result_size> res;
  std::copy(arr.begin(), arr.begin() + Result_size, res.begin());
  if (Array_size == Result_size)
    return res;

  // smallest of the 3 in the largest array
  int small_i = smallest_index(res);

  for (int i = Result_size; i < Array_size; ++i) {
    if (arr[i] > res[small_i]) {
      res[small_i] = arr[i];
      small_i = smallest_index(res);
    }
  }
  return res;
}

template <size_t N, typename Fun>
int least_iffy_index(const array<int, N> arr, Fun comparator) {
  int iffy_i = 0;
  for (int i = 1; i < N; ++i) {
    if (!comparator(arr[i], arr[iffy_i]) && !(arr[i] == arr[iffy_i]))
      iffy_i = i;
  }
  return iffy_i;
}

template <size_t Result_size, typename Fun, size_t Array_size>
std::array<int, Result_size> find_n_if(const array<int, Array_size> &arr,
                                       Fun comparator) {
  static_assert(Array_size >= Result_size, "can't find n largest of < n");
  array<int, Result_size> res;
  std::copy(arr.begin(), arr.begin() + Result_size, res.begin());
  if (Array_size == Result_size)
    return res;

  // small_i is not necessarily the smallest, depending on fun
  int iffy_i = least_iffy_index(res, comparator);

  for (int i = Result_size; i < Array_size; ++i) {
    if (comparator(arr[i], res[iffy_i])) {
      res[iffy_i] = arr[i];
      iffy_i = least_iffy_index(res, comparator);
    }
  }
  return res;
}

template <size_t Array_size>
int find_2nd_largest(const array<int, Array_size> &arr) {
  static_assert(Array_size >= 2, "can't find n largest of < n");
  // int res = find_n_if<1>(find_n_largest<2>(arr), std::less())[0];
  return find_n_if<1>(find_n_largest<2>(arr), std::less())[0];
}

int main(int argc, char *argv[]) {

  constexpr int s = 20;
  auto a = create_random_array<int, s>();
  // array<int, s> a;
  // for (int i = 0; i < s; ++i)
  //   a[i] = i;

  std::shuffle(a.begin(), a.end(), mt);
  print(a);
  auto b = find_3_largest(a);
  cout << "find_3_largest: ";
  print(b);
  auto c = find_n_largest<5>(a);
  cout << "find_n_largest: ";
  print(c);
  auto d = find_n_if<5>(a, std::less());
  cout << "find_n_if less: ";
  print(d);
  auto e = find_n_if<5>(a, std::greater());
  cout << "find_n_if greater: ";
  print(e);
  auto f = find_2nd_largest(a);
  cout << "find 2nd largest: " << find_2nd_largest(a) << endl;

  array<int, 5> res;
  std::partial_sort_copy(a.begin(), a.end(), res.begin(), res.end(),
                         std::less());
  cout << "using partial_sort_copy with less(): ";
  print(res);
  std::partial_sort_copy(a.begin(), a.end(), res.begin(), res.end(),
                         std::greater());

  cout << "using partial_sort_copy with greater(): ";
  print(res);
  return 0;
}
