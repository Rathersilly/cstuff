#include <algorithm>
#include <cassert>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>
using namespace fmt;
using namespace std;

void counting_sort(vector<int> &arr, int position = 1) {
  print("START counting sort\n");
  vector<int> memo(10);

  for (size_t i = 0; i < arr.size(); ++i) {
    memo[(arr[i] / position) % 10]++;
  }
  print("arr:  {}\n", arr);
  // print("memo: {}\n", memo);
  arr.clear();
  for (size_t i = 0; i < 10; ++i) {
    for (size_t j = 0; j < memo[i]; ++j) {
      arr.push_back(i);
    }
  }
  print("arr:  {}\n", arr);
  print("END   counting sort\n");
}
// not done
void radix_sort(vector<int> &arr) {
  int max_val = *(std::max_element(arr.begin(), arr.end()));

  print("max_val: {}\n", max_val);
  vector<vector<int>> memo(3);
  for (int i = 1; max_val / i > 0; i *= 10) {
    print("loop\n");
    print("arr:  {}\n", arr);
    counting_sort(arr, i);
    print("arr:  {}\n", arr);
    memo[i - 1] = arr;
    print("arr:  {}\n", arr);
    print("memo: {}\n", memo[i - 1]);
  }

  // loop through arr, checking first digit
  //
}
