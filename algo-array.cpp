// https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/
#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
using namespace std;

template <typename T> int maxSumSubArray(T a, T b) {
  T best_start = a;
  T best_end = a;
  T curr_start = a;
  T curr_end = a;
  int current_sum = 0;
  int max_sum = *a;
  for (auto i = a; i != b; ++i) {
    current_sum += *a;
    // keep going
    if (max_sum < current_sum) {
      max_sum = current_sum;
      curr_end = i;
    }
    // start over
    else {
      curr_start = i;
      current_sum =
    }
  }
  return max_sum;
}
int main(int argc, char *argv[]) {
  array<int, 8> arr{-2, -3, 4, -1, -2, 1, 5, -3};
  auto first = arr.begin();
  auto last = arr.end();
  cout << maxSumSubArray(arr.begin(), arr.end()) << endl;
}

