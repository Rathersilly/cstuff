// #include "../test/test.h"
#include <algorithm>
#include <color_macros.h>
#include <cstdio>
#include <iostream>
#include <iterator>
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

// TODO: benchmark these
// from https://gist.github.com/svdamani/dc57e4d1b00342d4507d
template <class Iterator> void InsertionSort(Iterator begin, Iterator end) {
  std::iter_swap(begin, std::min_element(begin, end));
  for (Iterator b = begin; ++b < end; begin = b)
    for (Iterator c = b; *c < *begin; --c, --begin)
      std::iter_swap(begin, c);
}

template <class RandomIt,
          class Compare =
              std::less<typename std::iterator_traits<RandomIt>::value_type>>
void insertion_sort(RandomIt first, RandomIt last, Compare cmp = Compare{}) {
  // TRACE_GREEN();
  if (first + 1 == last)
    return;
  for (auto i = first + 1; i != last; ++i) { // sorted subarray [first,i - 1)
    auto key = *i;
    auto j = i;
    while (j != first && cmp(key, *(j - 1))) {
      *j = *(j - 1);
      --j;
    }
    *j = key;
  }
}

template <class T, class Compare = std::less<T>>
void insertion_sort(vector<T> &vec, Compare cmp = Compare{}) {
  if (vec.size() <= 1)
    return;
  // loop invariant: A[0,i-1] = sorted subarray
  for (int i = 1; i < vec.size(); ++i) {
    int key = vec[i]; // key is the item to be inserted into sorted subarray
    int j = i - 1;    // j will iterate backward through sorted subarray
    while (j >= 0 && cmp(key, vec[j])) {
      vec[j + 1] = vec[j]; // key is smaller: shift the tested item up 1
      --j;
    }
    // we've found the proper index for key
    // and need to re-increment j since it went 1 too low
    vec[j + 1] = key;
  }
}
