#include <algorithm> // std::shuffle, sort
#include <array>
#include <chrono> // std::chrono::high_resolution_clock
#include <iostream>
#include <memory>
#include <random> // std::mt19937, uniform_int_distribution
#include <vector>

using namespace std;
int main(int argc, char *argv[]) {
  array<int, 4> arr1{0, 1, 2, 3};
  array<int, 4> arr2{0, 1, 2, 3};
  array<int, 5> arr3{0, 1, 2, 3};
  arr2 = arr1;
  cout << arr3[4] << endl;
  array<int, 0> a;
  cout << a.front();
  cout << a.back();

  return 0;
}
