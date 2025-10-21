#include <algorithm>
#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using namespace fmt;
void insertion_sort(vector<int> &arr) {
  // invariant: 0..i-1 is sorted
  for (size_t i = 1; i < arr.size(); ++i) {
    int key = arr[i];
    int j = i - 1;
    while (j >= 0 && key < arr[j]) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = key;
  }
}

vector<int> merge(vector<int> &a, vector<int> &b) {

  vector<int> result;
  result.reserve(a.size() + b.size());

  size_t ai = 0;
  size_t bi = 0;

  while (ai < a.size() && bi < b.size()) {
    if (a[ai] <= b[bi]) {
      result.push_back(a[ai++]);
    } else {
      result.push_back(b[bi++]);
    }
  }

  while (bi < b.size())
    result.push_back(b[bi++]);

  while (ai < a.size())
    result.push_back(a[ai++]);

  return result;
}

vector<int> merge_sort(vector<int> &arr) {
  if (arr.size() <= 1)
    return arr;
  if (arr.size() < 10) {
    insertion_sort(arr);
    return arr;
  }
  auto mid = arr.begin() + arr.size() / 2;
  vector<int> left{arr.begin(), mid};
  vector<int> right{mid, arr.end()};

  left = merge_sort(left);
  right = merge_sort(right);
  return merge(left, right);
}
