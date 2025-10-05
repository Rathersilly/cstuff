
#include <iterator>
#include <vector>

template <class InputIterator>
InputIterator
linear_search(InputIterator first, InputIterator last,
              typename std::iterator_traits<InputIterator>::value_type value) {

  for (; first != last; ++first) {
    if (*first == value)
      return first;
  }
  return last;
}

template <std::input_iterator It, std::sentinel_for<It> S, class T>
It linear_search_with_concept(It first, S last, const T &value) {
  for (; first != last; ++first) {
    if (*first == value)
      return first;
  }
  return last;
}
