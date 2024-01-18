// do this after LCPP templates
#include <chrono>
#include <random>
#include <vector>
/* template <class T> using ComparisonFunction = bool (*)(T, T); */
using ComparisonFunction = bool (*)(int, int);

template <class T>
void selection_sort(std::iterator<T> begin, std::iterator<T> end,
                    ComparisonFunction compfun) {
  // selection sort finds highest or lowest element, but the parameter
  // we are sorting by, and moves it to the sorted portion
  for (auto i = begin; i != end; ++i) {
  }
}

template <class T>
void selection_sort(std::iterator<T> begin, std::iterator<T> end,

std::iterator<vector<T>>find_lowest(

int main(int argc, char *argv[]) {
  std::mt19937 mt{
      std::chrono::high_resolution_clock::now().time_since_epoch().count()};
  std::vector<int> v;
  for (int i = 0; i < 10; ++i) {
    v.push_back(mt() % 10);
  }

  return 0;
}
