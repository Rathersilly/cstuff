#include "my_helpers.h"
#include <algorithm>
#include <array>
#include <benchmark/benchmark.h>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <vector>

// http://www.gotw.ca/gotw/054.htm
// Operation   Description
// ----------- -------------------------------------------
// grow        first, perform 1,000,000 push_back()s
// traverse    then traverse, simply incrementing
//               iterators, from begin() to end()
// at          then access each element in turn using at()
// shuffle     then random_shuffle() the entire container
// sort        then sort() the entire container (for list,
//               uses list::sort())
using namespace std;

static int container_size = 1000;

template <typename T> std::vector<T> RNG(int min, int max, int count) {
  std::uniform_int_distribution<> range{min, max};
  std::vector<T> res;
  res.reserve(count);
  for (int i = 0; i < count; ++i)
    res.push_back(range(mt));
  return res;
}
// template <typename T> T create_container() {
//   T container;
//   for (int i = 0; i < container_size; ++i) {
//     container.push_back(i);
//   }
//   return container;
// }

template <typename T> static void BM_grow(benchmark::State &s) {
  T container;
  for (auto i : RNG<int>(std::numeric_limits<int>::min(),
                         std::numeric_limits<int>::max(), container_size))
    container.push_back(i);
  while (s.KeepRunning()) {

    // container.reserve(container_size);
    for (int i = 0; i < container_size; ++i) {
      container.push_back(i);
      benchmark::DoNotOptimize(container);
    }
  }
}
// template <template <typename> class T>
template <typename T> static void BM_traverse(benchmark::State &s) {
  T container;
  for (auto i : RNG<int>(std::numeric_limits<int>::min(),
                         std::numeric_limits<int>::max(), container_size))
    container.push_back(i);
  while (s.KeepRunning()) {

    for (auto a = container.begin(); a != container.end(); ++a) {
      ++*a;
      benchmark::DoNotOptimize(container);
    }
  }
}
template <typename T> static void BM_at(benchmark::State &s) {
  T container;
  for (auto i : RNG<int>(std::numeric_limits<int>::min(),
                         std::numeric_limits<int>::max(), container_size))
    container.push_back(i);

  while (s.KeepRunning()) {

    for (int i = 0; i < container_size; ++i) {
      container.at(i);
      benchmark::DoNotOptimize(container);
    }
  }
}
template <typename T> static void BM_shuffle(benchmark::State &s) {
  T container;
  for (auto i : RNG<int>(std::numeric_limits<int>::min(),
                         std::numeric_limits<int>::max(), container_size))
    container.push_back(i);
  while (s.KeepRunning()) {
    std::shuffle(container.begin(), container.end(), mt);
    benchmark::DoNotOptimize(container);
  }
}

template <typename T> void SortContainer(T &container) {
  std::sort(container.begin(), container.end());
}

template <> void SortContainer<std::list<int>>(std::list<int> &container) {
  container.sort();
}

template <typename T> static void BM_sort(benchmark::State &s) {
  T container;
  for (auto i : RNG<int>(std::numeric_limits<int>::min(),
                         std::numeric_limits<int>::max(), container_size))
    container.push_back(i);
  while (s.KeepRunning()) {
    SortContainer(container);
    benchmark::DoNotOptimize(container);
    // std::sort(container.begin(), container.end());
    // container.sort();
  }
}

static void BM_grow_deque(benchmark::State &s) {
  while (s.KeepRunning()) {

    deque<int> container;
    for (int i = 0; i < container_size; ++i) {
      container.push_back(i);
    }
  }
}
static void BM_grow_list(benchmark::State &s) {
  while (s.KeepRunning()) {

    list<int> container;
    for (int i = 0; i < container_size; ++i) {
      container.push_back(i);
    }
  }
}
// static void BM_StringCreation(benchmark::State & state) {
//     std::string empty_string;
// }
// static void BM_grow_deque(benchmark::State &state) {
//   deque<int> container;
//   for (int i = 0; i < container_size; ++i) {
//     container.push_back(i);
//   }
// }
// static void BM_grow_list(benchmark::State &state) {
//   list<int> container;
//   for (int i = 0; i < container_size; ++i) {
//     container.push_back(i);
//   }
// }

BENCHMARK(BM_grow<vector<int>>);
BENCHMARK(BM_grow<deque<int>>);
// BENCHMARK(BM_grow<list<int>>);
BENCHMARK(BM_traverse<vector<int>>);
BENCHMARK(BM_traverse<deque<int>>);
// BENCHMARK(BM_traverse<list<int>>);
BENCHMARK(BM_at<vector<int>>);
BENCHMARK(BM_at<deque<int>>);
BENCHMARK(BM_shuffle<vector<int>>);
BENCHMARK(BM_shuffle<deque<int>>);
BENCHMARK(BM_sort<vector<int>>);
BENCHMARK(BM_sort<deque<int>>);
BENCHMARK(BM_sort<list<int>>);
BENCHMARK_MAIN();
