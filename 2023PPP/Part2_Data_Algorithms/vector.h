#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
/* #define INFO */

#include "vector_allocator.h"
/* #include "vector_iterator.h" */
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
using std::cout;
using std::endl;
// forward declarations not currently needed
/* template <typename T> void copy(T *from, int size_, T *to); */
/* template <typename T> void print_vector(const vector<T> &v); */

// simple copy function without using iterators
template <typename T> void copy(T *from, int size_, T *to) {
  for (int i = 0; i < size_; ++i) {
    to[i] = from[i];
  }
}
// copy with iterators
template <class I> void copy(I from, I to, I target) {

  for (auto i = from; i != to; ++i) {
    *target = *i;
    ++target;
  }
}

namespace my {
template <typename T, typename A = allocator<T>> class vector {
  /* template <typename T, typename A = allocator<T>> class vector { */
  /* invariant:
     if 0<=n<size_, elem[n] is element n
     size_ <= space_
     if size_ < space_ thre is space for (space-size_) doubles after
     elem[size_-1]
  */

  T *elem;
  A alloc;
  size_t size_;  // number of elements
  size_t space_; // maximum number of elements

  // constant or function to control how big to automatically resize
  /* constexpr size_t autoreserve_size = 10; */
  inline size_t autoreserve_size() { return size_ + size_ / 2; }
  inline void autoreserve() { reserve(autoreserve_size()); }

public:
  ///////////////////
  /// Iterator

  class iter {
    using iterator_concept [[maybe_unused]] = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using element_type = T;
    using pointer = element_type *;
    using reference = element_type &;

  private:
    T *curr;

  public:
    // an iterator (for a vector) could have an index - seems optional
    /* iter(T *t,size_t idx) : curr{t} {} */
    iter(T *t) : curr{t} {}

    iter &operator++() {
      curr += 1;
      return *this;
    }
    iter &operator--() {
      curr -= 1;
      return *this;
    }
    iter &next() { return ++curr; }
    iter &prev() { return --curr; }

    bool operator==(iter i) { return (i.curr == curr); }
    bool operator!=(iter i) { return (i.curr != curr); }
    T &operator*() { return *curr; }
  };

  iter begin() { return iter(elem); }
  const iter begin() const { return iter(elem); }
  iter end() { return iter(elem + size_); }
  const iter end() const { return iter(elem + size_); }

  ///////////////////
  //// Constructors (default, args, copy, move, destructor) see 18.4
  // default constructor
  vector() : size_{0}, elem{nullptr}, space_{0} { INFO; }

  // default constructor from args
  vector(size_t s) : size_{s}, elem{new T[s]}, space_{s} { INFO; }

  vector(int s)
      : size_{static_cast<size_t>(s)}, elem{new T[s]},
        space_{static_cast<size_t>(s)} {
    INFO;
  }

  // list initialization
  vector(std::initializer_list<T> lst)
      : size_{lst.size()}, elem{new T[lst.size()]}, space_{lst.size()} {
    INFO;
    std::copy(lst.begin(), lst.end(), elem);
  }

  // copy constructor
  vector(const vector &arg)
      : size_{arg.size()}, elem{new T[arg.size()]}, space_{arg.size()} {
    cout << "copy ctor ";
    INFO;

    copy(arg.begin(), arg.end(), begin());
  }

  // copy assignment ( 19.2.5 - doesnt make extra space_ )
  // make 1 vector's elements  = to another's
  vector<T> &operator=(const vector &a) {
    cout << "copy assignment " << endl;
    INFO;
    if (this == &a) { // same vector - nothing to do
      return *this;
    }
    if (a.size_ <= space_) { // enough space already
      for (int i = 0; i < a.size_; ++i) {
        elem[i] = a.elem[i];
      }
      size_ = a.size_;
      return *this;
    }

    // create new elem array with no extra reserved space_
    T *p = new T[a.size_];
    for (int i = 0; i < a.size_; ++i) {
      elem[i] = a.elem[i];
    }
    delete[] elem;
    elem = p;
    space_ = size_ = a.size_;

    return *this;
  }
  // move constructor (&& is rvalue reference)
  // - called when an object is initialized from rvalue, eg:
  // T a = std::move(b);  // b being type T
  // f(std::move(a));     // a being type T and f is void f(T t);
  // return a;            // a being type T and in T f();
  vector(vector<T> &&a) : size_{a.size_}, elem{a.elem} {
    // move constructor is used as fuction arg, so is deleted
    // when it goes out of scope
    cout << "move ctor ";
    INFO;
    a.size_ = 0;
    a.space_ = 0;
    a.elem = nullptr;
  }

  // move assignment
  vector<T> &operator=(vector<T> &&a) {
    cout << "move assign ";
    INFO;
    INFO;
    delete[] elem;
    size_ = a.size_;
    elem = a.elem;
    a.elem = nullptr;
    a.size_ = 0;
    a.space_ = 0;
    return *this;
  }
  // 7. destructor
  ~vector() {
    INFO;
    delete[] elem;
  }

  ///////////////////
  //// Access
  // without the &, this allows reading but not writing
  // because we wouldnt have it's address, just it's value

  T &operator[](int i) { return elem[i]; }

  // we also want to be able to read const element
  // eg.
  const T &operator[](int i) const { return elem[i]; }

  // at is [] but with range checking
  T &at(int i) {
    INFO;
    if (i < 0 || i >= size_) {
      throw std::range_error("out of range");
    }
    return elem[i];
  }

  ///////////////////
  //// Current Size
  size_t capacity() const { return space_; }
  size_t size() const { return size_; }

  ///////////////////
  //// Space
  // reserve function using custom allocator
  // basically new and delete operations are done
  // by the allocator.
  // construct and destroy are to be deprecated in c++20
  // so idk what if anything replaces them
  void reserve_with_allocator(size_t newalloc) {
    INFO;
    if (newalloc <= space_) {
      return;
    }
    T *p = alloc.allocate(newalloc);
    /* T *p = new T[newalloc]; */
    for (size_t i = 0; i < size_; ++i) {
      alloc.construct(&p[i], elem[i]);
      /* p[i] = elem[i]; */
    }
    for (size_t i = 0; i < size_; ++i) {
      alloc.destroy(&elem[i]);
    }
    alloc.deallocate(elem, space_);

    elem = p;
    space_ = newalloc;
  }
  // from before creating an allocator class
  /* void reserve_without_alloc( */
  void reserve(size_t newalloc) {
    INFO;
    if (newalloc <= space_) {
      return;
    }
    T *p = new T[newalloc];
    for (size_t i = 0; i < size_; ++i) {
      p[i] = elem[i];
    }
    delete[] elem;
    elem = p;
    space_ = newalloc;
  }

  // reserves if newsize is greater, initializing new element to 0
  // won't decrease space, just size - will 0 out "deleted" elements
  void resize(size_t newsize) {
    reserve(newsize);
    for (auto i = size_; i < newsize; ++i) {
      elem[i] = 0;
    }
    size_ = newsize;
  }

  void push_back(T d) {
    if (space_ == 0) {
      reserve(sizeof(T));
    }
    elem[size_] = d;
    ++size_;
  }
  void insert(T data, int index) {
    INFO;
    if (index > size_) {
      throw(std::out_of_range("invalid index"));
    }
    if (space_ == size_) {
      autoreserve();
    }
    for (int i = size_; i >= index; --i) {
      elem[i] = elem[i - 1];
    }
    size_ += 1;
    elem[index] = data;
  }
};
// print_vector function may not print all on one line as expected
// if PFUN is used because of buffering
template <typename T, typename A = allocator<T>>
void print_vector(const vector<T> &v) {
  for (auto i = 0; i < v.size(); ++i) {
    std::cout << v[i] << " ";
  }
  cout << endl;
}

// https://stackoverflow.com/questions/610245/where-and-why-do-i-have-to-put-the-template-and-typename-keywords
// the typename keyword is needed here so that compiler knows its a type
// - it can be ambiguous i guess?
// also this gives various errors - i think
// the compiler cant determine somevec.begin()'s type

template <typename T, typename A = allocator<T>>
void recursive_print_vector(typename vector<T>::iter b,
                            typename vector<T>::iter e) {
  if (b != e) {
    cout << *b << endl;
    recursive_print_vector(++b, e);
  }
}
} // namespace my
#endif
