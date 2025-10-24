
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <iterator>
#include <vector>

// Linear Search
template <class InputIterator>
InputIterator simple_linear_search(
    InputIterator first, InputIterator last,
    typename std::iterator_traits<InputIterator>::value_type value) {

  for (; first != last; ++first) {
    if (*first == value)
      return first;
  }
  return last;
}

// Linear Search with Concepts
// same as simple_linear_search, but with constraints on types used.
// The benefit of this is type safety and self documentation
// S will usually be an It but not necessarily
// - S just needs to be an iterator weakly comparable to It
template <std::input_iterator It, std::sentinel_for<It> S>
It linear_search_with_concept(
    It first, S last, typename std::iterator_traits<It>::value_type value) {

  for (; first != last; ++first) {
    if (*first == value)
      return first;
  }
  return last;
}

// Linear interpolation search
// - search range is progressively narrowed
// - by target's proximity to range's bounds
int interpolation_search(const std::vector<int> &arr, int x) {
  // returning -1 means not found
  if (arr.size() == 0)
    return -1;

  int lo = 0;
  int hi = arr.size() - 1;

  if (arr[lo] == x)
    return lo; // return if x is first element

  int prev_pos = -1; // flag to ensure progress each iteration

  while (hi >= lo) {
    if (arr[hi] == x)
      return hi; // return if x is last element

    auto pos =
        int(lo + (((double)x - arr[lo]) * (hi - lo)) / (arr[hi] - arr[lo]));
    pos = std::max(lo + 1, pos);

    // fmt::print("{} {} {}\n", lo, pos, hi);
    // fmt::print("{} {} {}\n", arr[lo], x, arr[hi]);
    // fmt::print("-----\n");

    if (pos == prev_pos) // havent found x and stopped progressing pos
      return -1;
    if (arr[pos] == x) // found x
      return pos;
    if (arr[pos] < x)
      lo = pos;
    else if (arr[pos] > x)
      hi = pos;

    prev_pos = pos;
  }
  return -1;
}
