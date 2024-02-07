// /////////////
// NOTE: my::array class
// in
//
// https://en.cppreference.com/w/cpp/language/aggregate_initialization
// std::array follows the rules of aggregate initialization:
//
// NOTE:
// T object = { arg1, arg2, ... };	(1)
// T object { arg1, arg2, ... };	(2)	(since C++11)
// T object = { .des1 = arg1 , .des2 { arg2 } ... };	(3)	(since C++20)
// T object { .des1 = arg1 , .des2 { arg2 } ... };	(4)	(since C++20)
//
// TODO: got as far as operations (on cppreference page)
// also can greatly improve iterator
// be sure to update test/test_array.cpp
#include <exception>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <typeinfo>

using namespace std;

namespace my {

template <typename T, std::size_t N> class array {
private:
  size_t size_;
  T *elem;

public:
  class Iter {
  protected:
    T *curr;

  public:
    Iter(T *arg) : curr{arg} {}
    T &operator*() { return *curr; }
    Iter &operator++() {
      curr += 1;
      return *this;
    }
    Iter &operator--() {
      curr -= 1;
      return *this;
    }
  };
  class RevIter : public Iter {
  public:
    using Iter::Iter; // Inherit constructors
    RevIter &operator++() {
      --(this->curr);
      return *this;
    }
    RevIter &operator--() {
      ++(this->curr);
      return *this;
    }
  };
  array() : size_{N} { elem = new T[N]; }
  // fulfill (1) of aggregate_initialization rules
  array(std::initializer_list<T> lst) : size_{N}, elem{new T[N]} {
    std::copy(lst.begin(), lst.end(), elem);
  }
  // fulfill (2) of aggregate_initialization rules
  array operator=(std::initializer_list<T> lst) {
    size_ = lst.size();
    elem = new T[size_];
    std::copy(lst.begin(), lst.end(), elem);
  }

  // copy constructor
  array(const array &other) : size_{other.size_}, elem{new T[size_]} {
    for (int i = 0; i < size_; ++i)
      elem[i] = other.elem[i];
  }
  // copy assignment
  array operator=(const array &arg) {
    size_ = arg.size();
    std::copy(arg.begin(), arg.end(), elem);
    return *this;
  }
  // move constructor
  array(array &&other) : size_{other.size_}, elem{other.elem} {
    other.size_ = 0;
    other.elem = nullptr;
  }
  // move assignment
  array &operator=(array &&other) {
    if (this != &other) {
      delete[] elem;
      size_ = other.size_;
      elem = other.elem;
      other.elem = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  // NOTE: Access (const versions omitted for brevity)
  //
  // at() is like [] but with bounds checking
  T &at(size_t pos) {
    if (pos < N && pos >= 0)
      return elem[pos];
    else
      // throw std::out_of_range("Whoa there that's out of range!");
      throw std::invalid_argument("invalid arg");
  }
  T &operator[](size_t n) { return elem[n]; }
  T &front() { return elem[0]; }        // std:array does not check range
  T &back() { return elem[size_ - 1]; } // std:array does not check range
  T *data() { return elem; }

  // NOTE: Iterators
  Iter begin() { return Iter(elem); }
  Iter end() { return Iter(elem + size_); }
  RevIter rbegin() { return RevIter(elem + size_ - 1); }
  RevIter rend() { return RevIter(elem - 1); }

  ~array() { delete[] elem; }

  size_t size() const { return size_; }
};
// NOTE: non-member functions
template <typename I, typename T, typename N> T &get(array<T, N> &arr) {}

} // namespace my
