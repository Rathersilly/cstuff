#ifndef MY_HELPERS_H
#define MY_HELPERS_H

#include <iostream>
#include <map>
#include <vector>
namespace my {

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
}

template <typename T> // print vector fn from learncpp
std::ostream &operator<<(std::ostream &s, const std::vector<T> &v) {
  s.put('{');
  for (char comma[]{'\0', ' ', '\0'}; const auto &e : v)
    s << comma << e, comma[0] = ',';
  return s << "}\n";
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
