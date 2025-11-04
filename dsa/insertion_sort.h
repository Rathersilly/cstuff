// #include "../test/test.h"
#include <algorithm>
#include <color_macros.h>
#include <cstdio>
#include <iterator>
#include <vector>
using namespace std;

// TODO: benchmark these
// from https://gist.github.com/svdamani/dc57e4d1b00342d4507d
template <class Iterator>
void insertion_sort_2fors(Iterator begin, Iterator end) {
  std::iter_swap(begin, std::min_element(begin, end));
  for (Iterator b = begin; ++b < end; begin = b)
    for (Iterator c = b; *c < *begin; --c, --begin)
      std::iter_swap(begin, c);
}

template <class BidirIt,
          class Compare =
              std::less<typename std::iterator_traits<BidirIt>::value_type>>
void insertion_sort(BidirIt first, BidirIt last, Compare cmp = Compare{}) {
  auto second = first; // second and test_pos needed for BidirIt to work
  ++second;            // with RandomIt we could just do first + 1
  if (second == last)
    return;
  for (auto i = second; i != last; ++i) { // sorted subarray [first,i - 1)
    auto key = *i;                        // key is value we are inserting
    auto key_pos = i;        // current position of value we are inserting
    auto test_pos = key_pos; // we compare test_pos vs key_pos
    --test_pos;              // test_pos is index to left of key_pos
    while (key_pos != first && cmp(key, *(test_pos))) {
      *key_pos = *(test_pos);
      --key_pos;
      --test_pos;
    }
    *key_pos = key;
  }
}

// template <class T, class Compare = std::less<T>>
// void insertion_sort(vector<T> &vec, Compare cmp = Compare{}) {
//   if (vec.size() <= 1)
//     return;
//   // loop invariant: A[0,i-1] = sorted subarray
//   for (size_t i = 1; i < vec.size(); ++i) {
//     int key = vec[i]; // key is the item to be inserted into sorted subarray
//     int j = i - 1;    // j will iterate backward through sorted subarray
//     while (j >= 0 && cmp(key, vec[j])) {
//       vec[j + 1] = vec[j]; // key is smaller: shift the tested item up 1
//       --j;
//     }
//     // we've found the proper index for key
//     // and need to re-increment j since it went 1 too low
//     vec[j + 1] = key;
//   }
// }
