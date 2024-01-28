// iota class - from cppref
#include "my_helpers.h"
#include <numeric> // std::iota
#include <vector>

namespace my {

template <typename ForwardIt, typename T>
void iota(ForwardIt first, ForwardIt last, T value) {
  for (; first != last; ++first, ++value) {
    *first = value;
  }
}
} // namespace my

int main(int argc, char *argv[]) {
  std::vector<int> foo(5);
  my::print_vector(foo); // 0, 0, 0, 0, 0
  my::iota(foo.begin(), foo.end(), -3);
  my::print_vector(foo); // -3, -2, -1, 0, 1

  return 0;
}
