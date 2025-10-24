// g++ -std=c++20 foo.cpp -lCatch2Main -lCatch2

#include <algorithm>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <initializer_list>
#include <iterator>
#include <random>
#include <vector>
std::mt19937 mt(std::random_device{}());

// #include "merge_sort.h"

using namespace std;
using namespace fmt;

void myshuffle(vector<int> &v) {
  std::shuffle(v.begin(), v.end(), mt);

  //
}
void insort(vector<int> &arr) {
  auto cmp = std::less<int>{};
  if (arr.size() <= 1)
    return;

  for (int i = 1; i < arr.size(); ++i) {
    auto key = arr[i];
    int j = i - 1;
    while (j >= 0 && cmp(key, arr[j])) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = key;
  }
}
vector<int> merge(const vector<int> &a, const vector<int> &b) {
  auto cmp = std::less<int>{};
  vector<int> res;
  res.reserve(a.size() + b.size());
  size_t ai = 0;
  size_t bi = 0;

  print("a and b: {} ", a);
  print("{}\n", b);
  while (ai < a.size() && bi < b.size()) {
    if (cmp(a[ai], b[bi])) {
      res.push_back(a[ai]);
      ++ai;
    } else {
      res.push_back(b[bi]);
      ++bi;
    }
  }
  while (ai < a.size()) {
    res.push_back(a[ai]);
    ++ai;
  }
  while (bi < b.size()) {
    res.push_back(b[bi]);
    ++bi;
  }
  print("MERGED {}\n", res);
  return res;
}
vector<int> merge_sort(vector<int> &arr) {
  if (arr.size() <= 1)
    return arr;

  auto mid = arr.size() / 2;
  vector<int> left, right;
  std::copy(arr.begin(), arr.begin() + mid, std::back_inserter(left));
  std::copy(arr.begin() + mid, arr.end(), std::back_inserter(right));
  print("left and right: {} ", left);
  print("{}\n", right);
  left = merge_sort(left);
  right = merge_sort(right);
  print("left and right b4 merge: {} ", left);
  print("{}\n", right);
  return merge(left, right);
}

int main(int argc, char *argv[]) {

  auto gen = [count = 0]() mutable { return count++; };
  vector<int> arr1(10);
  vector<int> arr2(10);

  std::generate(arr1.begin(), arr1.end(),
                [a = -2]() mutable { return a += 2; });
  std::generate(arr2.begin(), arr2.end(),
                [a = -1]() mutable { return a += 2; });
  print("{}\n", arr1);
  print("{}\n", arr2);
  auto m = merge(arr1, arr2);
  print("{}\n", m);
  std::shuffle(m.begin(), m.end(), mt);
  print("{}\n", m);
  m = merge_sort(m);
  print("{}\n", m);
}
