#ifndef VECTOR_H
#define VECTOR_H

#define GREEN "\033[32m" /* Green */
#define RESET "\033[0m"
#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
/* #define INFO */

#include <algorithm>
#include <cstddef>
#include <iostream>
using std::cout;
using std::endl;
/* template <typename T> void copy(T *from, int sz, T *to); */
/* template <typename T> void print_vector(const vector<T> &v); */

// simple copy function without using iterators
template <typename T> void copy(T *from, int sz, T *to) {
  for (int i = 0; i < sz; ++i) {
    to[i] = from[i];
  }
}
template <typename T> class vector;
template <typename T> void print_vector(const vector<T> &v) {
  for (auto i = 0; i < v.size(); ++i) {
    std::cout << v[i] << " ";
  }
  cout << endl;
}

template <typename T> class vector {
  /* invariant:
     if 0<=n<sz, elem[n] is element n
     sz <= space_
     if sz < space_ thre is space for (space-sz) doubles after elem[sz-1]
  */

  size_t sz;
  T *elem;
  size_t space_;

public:
  ///////////////////
  //// Constructors (default, args, copy, move, destructor) see 18.4
  // default constructor
  vector() : sz{0}, elem{nullptr}, space_{0} { INFO; }

  // default constructor from args
  vector(size_t s) : sz{s}, elem{new T[s]}, space_{s} { INFO; }

  vector(int s)
      : sz{static_cast<size_t>(s)}, elem{new T[s]},
        space_{static_cast<size_t>(s)} {
    INFO;
  }

  // list initialization
  vector(std::initializer_list<T> lst)
      : sz{lst.size()}, elem{new T[sz]}, space_{lst.size()} {
    INFO;
    std::copy(lst.begin(), lst.end(), elem);
  }

  // copy constructor
  vector(const vector &arg) : sz{arg.sz}, elem{new T[sz]}, space_{arg.sz} {
    INFO;
    copy(arg.elem, arg.sz, elem);
  }

  // copy assignment ( 19.2.5 - doesnt make extra space_ )
  // make 1 vector's elements  = to another's
  vector<T> &operator=(const vector &a) {
    if (this == &a) { // same vector - nothing to do
      return *this;
    }
    if (a.sz > space_) { // enough space already
      for (int i = 0; i < a.sz; ++i) {
        elem[i] = a.elem[i];
      }
    }

    // create new elem array with no extra reserved space_
    T *p = new T[a.sz];
    for (int i = 0; i < a.sz; ++i) {
      elem[i] = a.elem[i];
    }
    delete[] elem;
    elem = p;
    space_ = sz = a.sz;

    return *this;
  }
  // move constructor (&& is rvalue reference)
  vector(vector<T> &&a) : sz{a.sz}, elem{a.elem} {
    // move constructor is used as fuction arg, so is deleted
    // when it goes out of scope
    INFO;
    a.sz = 0;
    a.space_ = 0;
    a.elem = nullptr;
  }

  // move assignment
  vector<T> &operator=(vector<T> &&a) {
    INFO;
    delete[] elem;
    sz = a.sz;
    elem = a.elem;
    a.elem = nullptr;
    a.sz = 0;
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
  T &operator[](int i) { return elem[i]; }
  // we want to be able to read const element
  T operator[](int i) const { return elem[i]; }

  ///////////////////
  //// Current Size
  size_t capacity() const { return space_; }
  size_t size() const { return sz; }

  ///////////////////
  //// Space
  void reserve(size_t newalloc) {
    INFO;
    if (newalloc <= space_) {
      return;
    }
    T *p = new T[newalloc];
    for (size_t i = 0; i < sz; ++i) {
      p[i] = elem[i];
    }
    delete[] elem;
    elem = p;
    space_ = newalloc;
  }

  void resize(size_t newsize, T default_ = T()) {
    reserve(newsize);
    for (auto i = sz; i < newsize; ++i) {
      elem[i] = 0;
    }
    sz = newsize;
  }

  void push_back(T d) {
    if (space_ == 0) {
      reserve(sizeof(T));
    }
    elem[sz] = d;
    ++sz;
  }
};

#endif
