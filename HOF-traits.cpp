// NOTE: Traits
// -  from learncpp + tcpppl 28.2.4 + gpt
// Traits can be considered as a bundle of type functions
// (like is_pod, is_pointer, is_null_pointer, etc) see <type_traits>
// TODO: This file is probably complete but need another one for
// concepts/requirements

#include <iostream>
#include <iterator>
#include <list>
#include <vector>
using namespace std;

// template <typename iterator> struct my_iterator_traits {
//   using difference_type = typename iterator::difference_type;
//   using value_type = typename iterator::value_type;
//   using pointer = typename iterator::pointer;
//   using reference = typename iterator::reference;
//   using iterator_category = typename iterator::iterator_category;
// };

// NOTE: Primary template for generic iterators
// - this is needed because not all iterators have the same set of nested types.
// - "typename = void" is a hack to manipulate Template Argument Deduction.
//      It allows us to use a partial specialization for pointers
//      without confusing the compiler
template <typename Iterator, typename = void> struct my_iterator_traits {
  // Define default values for generic iterators
  using difference_type = std::ptrdiff_t;
  // using value_type = typename std::iterator_traits<Iterator>::value_type;
  using value_type = typename Iterator::value_type;
  // using pointer = typename std::iterator_traits<Iterator>::pointer;
  using pointer = typename Iterator::pointer;
  // using reference = typename std::iterator_traits<Iterator>::reference;
  using reference = typename Iterator::reference;
  // using iterator_category = typename
  // std::iterator_traits<Iterator>::iterator_category;
  using iterator_category = typename Iterator::iterator_category;
};

// NOTE: Partial specialization for pointers
// - allows my_reverse function args to be pointers as well as iterators
template <typename T>
struct my_iterator_traits<T *, std::enable_if_t<std::is_object_v<T>>> {
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = T *;
  using reference = T &;
  using iterator_category = std::random_access_iterator_tag;
};

template <class BidirIt> void my_reverse(BidirIt first, BidirIt last) {
  // typename std::iterator_traits<BidirIt>::difference_type n =
  typename my_iterator_traits<BidirIt>::difference_type n =
      std::distance(first, last);
  for (--n; n > 0; n -= 2) {
    typename std::iterator_traits<BidirIt>::value_type tmp = *first;
    *first++ = *--last;
    *last = tmp;
  }
}

template <typename T> struct MyTrait {
  // Metafunction to check if a type is integral
  static constexpr bool is_integral = std::is_integral<T>::value;

  // Metafunction to remove const qualification
  using remove_const = std::remove_const_t<T>;

  // Metafunction to add a pointer
  using add_pointer = std::add_pointer_t<T>;
};

int main() {
  typename my_iterator_traits<vector<int>::iterator>::difference_type foo;
  std::vector<int> v{1, 2, 3, 4, 5};
  my_reverse(v.begin(), v.end());
  for (int n : v)
    std::cout << n << ' ';
  std::cout << '\n';

  std::list<int> l{1, 2, 3, 4, 5};
  my_reverse(l.begin(), l.end());
  for (int n : l)
    std::cout << n << ' ';
  std::cout << '\n';

  int a[]{1, 2, 3, 4, 5};
  my_reverse(a, a + std::size(a));
  for (int n : a)
    std::cout << n << ' ';
  std::cout << '\n';

  //  std::istreambuf_iterator<char> i1(std::cin), i2;
  //  my_reverse(i1, i2); // compilation error: i1, i2 are input iterators

  // NOTE: MyTrait in action
  static_assert(MyTrait<int>::is_integral, "int is integral");

  using NonConstInt = MyTrait<const int>::remove_const;
  static_assert(std::is_same_v<NonConstInt, int>,
                "const int is transformed to int");

  using IntPointer = MyTrait<int>::add_pointer;
  static_assert(std::is_same_v<IntPointer, int *>, "pointer added to int");

  return 0;
}
