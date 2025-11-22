#include <algorithm>
#include <concepts>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <iostream>
#include <random>
#include <string>
#include <type_traits>

using namespace std;

std::mt19937 mt{std::random_device{}()};
using namespace std;

// creating Binary Function concept (like std::less)
// = is for types - determine what types are valid
// requires is for syntax - determine what expressions are valid
// - eg params, return, throws
// { foo } -> bar means the expression foo must eval to something satisfying bar

template <class Func, class T, class U>
concept Compare =
    std::same_as<T, U> && std::integral<T> &&
    std::equality_comparable_with<T, U> && requires(Func c, T t, U u) {
      { c(t, u) } -> std::convertible_to<bool>;
    };

template <class Func, class T, class U>
concept CompareDemo =
    requires(Func c, T t, U u) {
      // - 1. Simple Requirement (checking expression validity) ---
      // A requirement that the expression t < u must be well-formed (valid
      // syntax).
      t < u;

      // - 2. Type Requirement (see struct Cat below)
      // typename T::some_type ;
      // t.some_function();

      // - 3. Compound Requirement (checking return type) ---
      // Checks if the expression c(t, u) is valid AND its result is
      // convertible to bool.
      //
      { c(t, u) } -> std::convertible_to<bool>;
    } &&

    std::same_as<T, U> && // Type Relationship Check
    std::integral<T> &&   // Type Trait Check
    std::equality_comparable_with<T, U>;

// Notice Compare only takes 2 template args here - the first one is implied
template <std::bidirectional_iterator It,
          Compare<typename It::value_type, typename It::value_type> Cmp>
void insertion_sort(It first, It last, Cmp &cmp) {
  auto second = first;
  ++second;
  if (first == last || second == last)
    return;
  for (auto it = second; it != last; ++it) {
    auto key = *it;
    auto key_pos = it;
    auto test_pos = key_pos;
    --test_pos;
    while (key_pos != first && cmp(key, *test_pos)) {
      *key_pos = *test_pos;
      --key_pos;
      --test_pos;
    }
    *key_pos = key;
  }
}

// Check for existence of a member type, variable, function
template <class T>
concept CanSpeak = requires(T a) {
  typename T::Name;                               // check for member type
  a.name;                                         // check for member existence
  { a.name } -> std::convertible_to<std::string>; // or even stricter
  a.speak();                                      // check for member function
};

struct Cat {
  using Name = std::string;
  Name name = "Fluffy";
  void speak() const { cout << "Meow" << endl; }
};

template <CanSpeak T> void make_speak(const T &speaker) { speaker.speak(); }

int main(int argc, char *argv[]) {
  vector<int> vec(20);
  std::iota(vec.begin(), vec.end(), 0);
  fmt::print("{}\n", vec);
  std::shuffle(vec.begin(), vec.end(), mt);

  fmt::print("{}\n", vec);
  auto fun = [](int a, int b) { return a > b; };
  insertion_sort(vec.begin(), vec.end(), fun);

  fmt::print("{}\n", vec);

  Cat fluffy;
  make_speak(fluffy);
  return 0;
}
