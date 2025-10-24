#include <algorithm>
#include <array>
#include <cassert>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <random>
using namespace std;
using namespace fmt;

std::mt19937 mt{random_device{}()};
std::uniform_int_distribution<int> d3(0, 3);
int r3() { return d3(mt); };

// Move zeros to endo of container
// -- TODO: make this require T be comparable to 0 with concept
template <typename T, int N> void move_zeros_to_end(array<T, N> &arr) {

  auto last_nonzero_index = arr.size() - 1;
  while (last_nonzero_index >= 0 && arr[last_nonzero_index] == 0)
    --last_nonzero_index;

  for (int i = last_nonzero_index; i >= 0; --i) {
    if (arr[i] == 0) {
      swap(arr[i], arr[last_nonzero_index]);
      last_nonzero_index--;
    }
  }
}
int main(int argc, char *argv[]) {

  // test move_zeros_to_end
  std::array<int, 20> arr;
  ranges::generate(arr, r3);
  print("{}\n", arr);
  auto prev = arr;
  move_zeros_to_end<int, 20>(arr);
  print("{}\n", arr);
  assert(ranges::is_permutation(arr, prev));
  assert(ranges::count(arr, 0) == ranges::count(prev, 0));
  assert(ranges::count(arr, 0) == ranges::count(prev, 0));
  assert(ranges::is_partitioned(arr, [](int x) { return x != 0; }));

  return 0;
}
