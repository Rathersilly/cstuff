// Merge Sort - 2 methods:
// merge_sort() - super naive
// merge_sort_inplace() - a little better
#include <fmt/base.h>
#include <fmt/ranges.h>
#include <vector>

using namespace std;
using namespace fmt;

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
  // print("merge sort: {}", arr);
  if (arr.size() <= 1)
    return arr;

  auto mid = arr.begin() + arr.size() / 2;

  vector<int> left(arr.begin(), mid);
  vector<int> right(mid, arr.end());

  left = merge_sort(left);
  right = merge_sort(right);
  // print("{}", left);
  // print("{}", right);
  return merge(left, right);
}

template <typename T>
void merge_impl(std::vector<T> &arr, size_t left, size_t mid, size_t right,
                std::vector<T> &temp) {
  size_t i = left; // start of left half
  size_t j = mid;  // start of right half
  size_t k = left; // write position in temp

  while (i < mid && j < right) {
    if (arr[i] <= arr[j])
      temp[k++] = arr[i++];
    else
      temp[k++] = arr[j++];
  }

  // copy remaining elements
  while (i < mid)
    temp[k++] = arr[i++];
  while (j < right)
    temp[k++] = arr[j++];

  // copy merged range back to arr
  for (size_t p = left; p < right; ++p)
    arr[p] = temp[p];
}

template <typename T>
void merge_sort_impl(std::vector<T> &arr, size_t left, size_t right,
                     std::vector<T> &temp) {
  if (right - left <= 1)
    return;

  auto mid = left + (right - left) / 2;

  merge_sort_impl(arr, left, mid, temp);
  merge_sort_impl(arr, mid, right, temp);
  merge_impl(arr, left, mid, right, temp);
}

template <typename T> void merge_sort_inplace(std::vector<T> &arr) {
  vector<T> temp(arr.size());
  merge_sort_impl(arr, 0, arr.size(), temp);
}
