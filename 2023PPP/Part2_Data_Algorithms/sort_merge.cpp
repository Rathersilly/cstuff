// TODO make this work with other containers
// also the function is generally merge_sort(a,start_index,end_index)
// where a is always the whole array - see if that effects resources
#include "/home/rsil/cstuff/2023PPP/Part2_Data_Algorithms/my_helpers.h"
#include <algorithm> // std::shuffle, sort
#include <chrono>
#include <color_macros.h>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

using namespace std;
using namespace my;

template <class T> vector<T> merge(const vector<T> &a, const vector<T> &b) {
  /* PFUN; */
  /* print_vector(a); */
  /* print_vector(b); */
  auto iter_a = a.begin();
  auto iter_b = b.begin();
  vector<T> memo;
  // this is more verbose than needed
  // while (true) {
  //
  //   if (iter_a == a.end()) {
  //     if (iter_b == b.end()) {
  //       break;
  //     } else {
  //       memo.push_back(*iter_b);
  //       ++iter_b;
  //     }
  //   } else if (iter_b == b.end()) {
  //     memo.push_back(*iter_a);
  //     ++iter_a;
  //   } else if (*iter_a < *iter_b) {
  //     memo.push_back(*iter_a);
  //     ++iter_a;
  //   } else {
  //     memo.push_back(*iter_b);
  //     ++iter_b;
  //   }
  // }
  //
  // add to memo until one of the iterators hits the end
  while (iter_a != a.end() && iter_b != b.end()) {
    if (*iter_a < *iter_b) {
      memo.push_back(*iter_a);
      ++iter_a;
    } else {
      memo.push_back(*iter_b);
      ++iter_b;
    }
  }
  // add the remaining elements (one of these is sorted, the other is empty)
  memo.insert(memo.end(), iter_a, a.end());
  memo.insert(memo.end(), iter_b, b.end());

  /* std::cout << GREEN; */
  /* print_vector(memo); */
  /* std::cout << RESET; */
  return memo;
}

template <class T>
vector<T> merge_sort(typename vector<T>::const_iterator first,
                     typename vector<T>::const_iterator last) {
  PFUN;
  auto size = last - first;
  if (size < 2)
    return vector<T>(first, last);
  // cout << "first last-1 size: " << *first << " " << *(last - 1) << " " <<
  // size << endl;
  return merge(merge_sort<T>(first, first + size / 2),
               merge_sort<T>(first + size / 2, last));
}

int main(int argc, char *argv[]) {

  std::mt19937 mt{static_cast<std::mt19937::result_type>(
      std::chrono::high_resolution_clock::now().time_since_epoch().count())};
  std::vector<int> v;
  for (int i = 0; i < 6; ++i) {
    /* v.push_back(mt() % 10); */
    v.push_back(i);
  }
  std::shuffle(v.begin(), v.end(), mt);
  /* std::reverse(v.begin(), v.end()); */
  /* vector<int> vv = my::sort(v); */
  vector<int> vv = merge_sort<int>(v.begin(), v.end());
  my::print_vector(v);
  my::print_vector(vv);
  return 0;
}
