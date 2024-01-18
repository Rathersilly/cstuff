#ifndef MY_HELPERS_H
#define MY_HELPERS_H

#include <iostream>
#include <vector>
namespace my {

template <typename T> void print_vector(const std::vector<T> &v) {
  for (auto i = 0; i < v.size(); ++i) {
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
}
} // namespace my
#endif // !MY_HELPERS_H
