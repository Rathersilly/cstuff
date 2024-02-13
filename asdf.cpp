#include "my_helpers.h"
#include <algorithm> // std::shuffle, sort
#include <array>
#include <cassert>
#include <chrono> // std::chrono::high_resolution_clock
#include <iostream>
#include <random> // std::omt19937, uniform_int_distribution
#include <thread>
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;      // nanoseconds, system_clock, seconds

using namespace my;
using namespace std;

template <size_t N, typename Fun>
int least_iffy_index(const array<int, N> &arr, Fun comparator) {
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
  print(arr);
  cout << endl;
  array<int, Result_size> res;
  cout << "here" << endl;
  print(arr);
  cout << endl;
  print(arr);
  cout << endl;
  cout << "arraysize " << Array_size << endl;
  cout << "before copy" << endl;

  std::copy(arr.begin(), arr.begin() + Result_size, res.begin());
  print(arr);
  cout << endl;
  cout << "WTF arr has been changed" << endl;
  print(arr);
  cout << endl;
  if (Array_size == Result_size)
    return res;
  print(arr);
  cout << endl;

  // small_i is not necessarily the smallest, depending on fun
  int iffy_i = least_iffy_index(res, comparator);

  for (int i = Result_size; i < Array_size; ++i) {
    if (comparator(arr[i], res[iffy_i])) {
      res[iffy_i] = arr[i];
      iffy_i = least_iffy_index(res, comparator);
      print(arr);
      cout << '\n';
      sleep_for(milliseconds(10));
    }
  }
  return res;
}
int main(int argc, char *argv[]) {
  std::mt19937 mt{static_cast<std::mt19937::result_type>(
      std::chrono::high_resolution_clock::now().time_since_epoch().count())};

  constexpr int s = 20;
  array<int, s> a;
  for (int i = 0; i < s; ++i)
    a[i] = i;
  std::shuffle(a.begin(), a.end(), mt);

  print(a);
  cout << '\n';
  auto e = find_n_if<5>(a, std::greater());
  print(a);
  cout << '\n';
  print(e);
  return 0;
}
