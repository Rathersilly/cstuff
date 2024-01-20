// do this after LCPP templates
#include "Part2_Data_Algorithms/my_helpers.h"
#include <algorithm> // std::shuffle, sort
#include <chrono>
#include <color_macros.h>
#include <iterator>
#include <random>
#include <vector>

using namespace std;

template <class T> using ComparisonFn = bool (*)(T, T);
template <class T> bool descending(T a, T b) { return a < b; }
template <class T> bool ascending(T a, T b) { return a > b; }

template <class T, class U>
int find_best_index(T begin, T end, ComparisonFn<U> compfun = ascending) {
  if (end - begin < 2) // return 0 if range has only 1 element
    return 0;

  int best_index = 0;
  int i = 0;
  // loop from begin to end - 1 , because we are comparing a and ++a
  for (auto a = begin; a != end - 1; ++a) {
    /* cout << "best_index, current_index:  " << best_index << " " << i << endl;
     */
    if (compfun(*(begin + best_index), *(a + 1))) {

      // cout << "true: " << *(begin + best_index) << " > " << *(a + 1) << endl;

      best_index = i + 1;
    }
    ++i;
  }
  /* cout << "returning: " << best_index << endl; */
  return best_index;
}

template <class T>
void selection_sort(vector<T> &vec, ComparisonFn<T> compfun = ascending) {
  if (vec.size() < 2)
    return;

  int best_index;
  int i = -1;

  for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
    /* my::print_vector(vec); */
    ++i;

    best_index = i + find_best_index(iter, vec.end(), compfun);
    /* cout << "i and best_index: " << i << " " << best_index << endl; */
    if (best_index == 0) {
      continue;
    }
    std::swap(vec[i], vec[best_index]);
  }
}

int main(int argc, char *argv[]) {
  std::mt19937 mt{
      std::chrono::high_resolution_clock::now().time_since_epoch().count()};
  std::vector<int> v;
  for (int i = 0; i < 50; ++i) {
    /* v.push_back(mt() % 10); */
    v.push_back(i);
  }
  std::shuffle(v.begin(), v.end(), mt);
  std::reverse(v.begin(), v.end());
  my::print_vector(v);
  selection_sort(v);
  my::print_vector(v);
  selection_sort(v, descending);
  my::print_vector(v);

  return 0;
}
