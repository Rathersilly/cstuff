#ifndef MY_HELPERS_H
#define MY_HELPERS_H
// INFO: functions to print arrays and vectors
// create random numbers, random arrays
// TODO: generalize the random array function - make it work
// for any container

#include <array>
#include <chrono> // std::chrono::high_resolution_clock
#include <iostream>
#include <map>
#include <random> // std::mt19937, uniform_int_distribution
#include <vector>

// mt() returns random number (uint_fast32_t)
static inline std::mt19937 mt{static_cast<std::mt19937::result_type>(
    std::chrono::high_resolution_clock::now().time_since_epoch().count())};
static inline std::uniform_int_distribution<> die12{1, 12};
static inline std::uniform_int_distribution<> die10{1, 10};

namespace my {

template <typename T> void print(T a, T b) {
  for (auto i = a; i != b; ++i) {
    std::cout << *i << ' ';
  }
}
template <typename T, std::size_t N> void print(std::array<T, N> &arg) {
  // for (auto a = arg.begin(); a != arg.end(); ++a) {
  for (const auto &element : arg) {
    std::cout << element << ' ';
  }
  std::cout << std::endl;
}
template <typename T, std::size_t N> void print(const std::array<T, N> &arg) {
  // for (auto a = arg.begin(); a != arg.end(); ++a) {
  for (const auto &element : arg) {
    std::cout << element << ' ';
  }
  std::cout << std::endl;
}

template <typename T> void print_vector(const std::vector<T> &v) {
  for (auto i = 0; i < v.size(); ++i) {
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
}
template <typename T, typename U> void print_map(const std::map<T, U> &m) {
  for (auto a = m.begin(); a != m.end(); ++a) {
    std::cout << a->first << "\t\t" << a->second << std::endl;
  }
  std::cout << std::endl;
}

template <typename T> // print vector fn from learncpp
std::ostream &operator<<(std::ostream &s, const std::vector<T> &v) {
  s.put('{');
  for (char comma[]{'\0', ' ', '\0'}; const auto &e : v)
    s << comma << e, comma[0] = ',';
  return s << "}\n";
}
template <typename T, size_t N> std::array<T, N> create_array() {
  std::array<T, N> a;
  for (int i = 0; i < N; ++i)
    a[i] = i;
  return a;
}
template <typename T, size_t N> std::array<T, N> create_shuffled_array() {
  std::array<T, N> a;
  for (int i = 0; i < N; ++i)
    a[i] = i;
  a.shuffle();
  return a;
}
template <typename T, size_t N>
std::array<T, N> create_random_array(int min = 0, int max = 100) {
  std::uniform_int_distribution<> distrib(min, max);
  std::array<T, N> a;
  for (int i = 0; i < N; ++i)
    a[i] = distrib(mt);
  return a;
}

/* template <typename T, typename U> */
/* void print_range(const T<U>::iterator first, const T<U>::iterator last, ) {
 */
/*   for (auto a = first; a != last; ++a) { */
/*     std::cout << *a << " "; */
/*   } */
/*   std::cout << std::endl; */
/* } */

} // namespace my

#endif // !MY_HELPERS_H
