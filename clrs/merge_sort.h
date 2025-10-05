
// #include "../test/test.h"
#include <algorithm>
#include <color_macros.h>
#include <iostream>
#include <thread>
#include <vector>
using namespace std;
inline void print_vector(const vector<int> vec, string msg = "") {
  cout << msg;
  for (auto &a : vec) {
    cout << a << " ";
  }
  cout << endl;
}
inline void print_vector(const vector<int>::iterator first,
                         const vector<int>::iterator last, string msg = "") {
  cout << msg;
  for (auto a = first; a != last; ++a) {
    cout << *a << " ";
  }
  cout << endl;
}

template <class Iterator> Iterator merge(Iterator first, Iterator last) {}
template <class Iterator,
          class Compare =
              std::less<typename std::iterator_traits<Iterator>::value_type>>
void merge_sort(Iterator first, Iterator last, Compare cmp = Compare{}) {

  if (first + 1 >= last)
    return;

  auto dist = last - first;
  auto mid = (last - first) / 2;

  merge(merge_sort(first, first + mid), merge_sort(first + mid), last);
}

template <class T> vector<T> merge(vector<T> left, vector<T> right) {}

template <class T> vector<T> merge(vector<T> &left, vector<T> &right) {
  // invariant - left and right are sorted
  size_t size = left.size() + right.size();
  vector<T> res;
  res.reserve(size);
  for (int i; i < left.size(); ++i) {
    while (right)
      if (left[i])
        res.push_back
  }
}

template <class T, class Compare = std::less<T>>
void merge_sort(vector<T> &vec, T begin, T end, Compare cmp = Compare{}) {
  if (vec.size() <= 1)
    return;
  vector<T> left = vec;

  merge(merge_sort()) merge_sort(first_half, second_half);
}
