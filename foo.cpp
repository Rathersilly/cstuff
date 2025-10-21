// g++ -std=c++20 foo.cpp -lCatch2Main -lCatch2

#include <algorithm>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <iterator>
#include <random>

// #include "merge_sort.h"

using namespace std;
using namespace fmt;

std::mt19937 mt{std::random_device{}()};

int main(int argc, char *argv[]) {

  auto gen = [count = 0]() mutable { return count++; };
  vector<int> arr1(5);
  vector<int> arr2(5);

  std::iota(arr1.begin(), arr1.end(), 0);
  std::iota(arr2.begin(), arr2.end(), 3);
  print("hi");
  print("{}\n", arr1);
  print("{}\n", arr2);
  // auto sorted_arr = merge_and_insertion_sort(arr);
  vector<int> intersection;
  std::set_intersection(arr1.begin(), arr1.end(), arr2.begin(), arr2.end(),
                        back_inserter(intersection));
  print("{}\n", intersection);
  // std::set_intersection(arr1.begin(), arr1.end(), sorted_arr.begin(),
  //                       sorted_arr.end(), back_inserter(intersection));
}
