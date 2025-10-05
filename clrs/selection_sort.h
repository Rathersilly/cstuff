
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
template <class Iterator>
void shortest_selection_sort(Iterator first, Iterator last) {
  for (auto it = first; it != last; ++it) {
    std::iter_swap(min_element(it, last), it);
  }
}

template <class Iterator,
          class Compare =
              std::less<typename std::iterator_traits<Iterator>::value_type>>
void selection_sort(Iterator first, Iterator last, Compare cmp = Compare{}) {

  if (first + 1 >= last)
    return;

  for (auto i = first; i != last - 1; ++i) {
    auto smallest_it = i;
    for (auto j = i + 1; j != last; ++j) {
      // std::this_thread::sleep_for(10ms);
      // printf("*i: %i *j %i\n", *i, *j);
      if (cmp(*j, *smallest_it)) {
        smallest_it = j;
      }
    }
    // std::swap(*smallest_it, *i);
    std::iter_swap(smallest_it, i);
    print_vector(first, last);
  }
}

template <class T, class Compare = std::less<T>>
void selection_sort(vector<T> &vec, Compare cmp = Compare{}) {
  // loop invariant: A[0,i] is sorted
  // search unsorted subarray for smallest value,
  // swap it with first unsorted value and increment i
  if (vec.size() <= 1)
    return;
  for (int i = 0; i < vec.size() - 1; ++i) {
    int smallest_index = i;
    for (int j = i + 1; j < vec.size(); ++j) {
      if (vec[j] < vec[smallest_index])
        smallest_index = j;
    }
    // printf("Swap: %i, %i\n", vec[smallest_index], vec[i]);

    std::swap(vec[smallest_index], vec[i]);
    // print_vector(vec);
  }
}
