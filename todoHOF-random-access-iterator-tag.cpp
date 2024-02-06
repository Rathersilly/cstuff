// testing that if it looks like an iterator and quacks like an iterator
// it is an iterator
// Ah, but it needs to be superlass of std::iterator for std::sort to use it.
// TODO: inheriting from random_access_iterator_tag is harder than it looks
// theres a LOT you have to define - gonna leave this for later
#include <algorithm> // std::shuffle, sort
#include <chrono>    // std::chrono::high_resolution_clock
#include <iostream>
#include <memory>
#include <random> // std::mt19937, uniform_int_distribution
#include <vector>

using namespace std;
std::mt19937::result_type mt = static_cast<std::mt19937::result_type>(
    std::chrono::high_resolution_clock::now().time_since_epoch().count());

class MyIntArray {
private:
  int *elem;

public:
  // To satisfy the requirements of random_access_iterator_tag
  // Iter must have all the right operators defined
  class Iter
      : std::iterator<std::random_access_iterator_tag, // iterator_category
                      int,                             // value type
                      std::ptrdiff_t,                  // difference
                      const int *,                     // pointer
                      int                              // reference
                      > {
    int *ptr;

  public:
    using difference_type = std::ptrdiff_t;
    Iter(int *p) : ptr{p} {}
    int &operator*() const { return *ptr; }
    Iter &operator++() {
      ++ptr;
      return *this;
    }
    Iter &operator--() {
      --ptr;
      return *this;
    }

    bool operator==(Iter i) { return ptr == i.ptr; }

    // std::ptrdiff_t operator+(const Iter &other) const {
    //   return ptr + other.ptr;
    // }
    //
    // std::ptrdiff_t operator-(const Iter &other) const {
    //   return ptr - other.ptr;
    // }
    Iter operator+(std::ptrdiff_t n) const { return Iter(ptr + n); }
    Iter operator-(std::ptrdiff_t n) const { return Iter(ptr - n); }
    Iter &operator+=(std::ptrdiff_t n) {
      ptr += n;
      return *this;
    }
    Iter &operator-=(std::ptrdiff_t n) {
      ptr -= n;
      return *this;
    }
    bool operator!=(Iter i) { return ptr != i.ptr; }
    // Iter operator++(int) {}
  };
  int size;
  MyIntArray(int n) : size{n} { elem = new int[n]; }
  int &operator[](int i) { return elem[i]; }
  Iter begin() { return Iter(elem); }
  Iter end() { return Iter(elem + size); }
};
void print_myintarray(MyIntArray arr) {
  for (MyIntArray::Iter i = arr.begin(); i != arr.end(); ++i) {
    cout << *i;
  }
  cout << endl;
}

int main() {
  MyIntArray arr(5);
  for (int i = 0; i < arr.size; ++i)
    arr[i] = i;

  for (int i = 0; i < arr.size; ++i)
    cout << arr[i];
  std::shuffle(arr.begin(), arr.end(), mt);
  print_myintarray(arr);
  // std::sort(arr.begin(), arr.end());
  print_myintarray(arr);
  *(arr.begin()) = 7;
  for (auto i = arr.begin(); i != arr.end(); ++i) {
    *i += 7;
  }

  return 0;
}
