#ifndef VECTOR_H
#define VECTOR_H

#include <iterator>
#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
/* #define INFO */

#include "vector_allocator.h"
#include "vector_iterator.h"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
using std::cout;
using std::endl;
// forward declarations not currently needed
/* template <typename T> void copy(T *from, int sz, T *to); */
/* template <typename T> void print_vector(const vector<T> &v); */

// simple copy function without using iterators
template <typename T> void copy(T *from, int sz, T *to) {
  for (int i = 0; i < sz; ++i) {
    to[i] = from[i];
  }
}
template <typename T, typename A = allocator<T>> class vector;

template <typename T, typename A> class vector {
  /* template <typename T, typename A = allocator<T>> class vector { */
  /* invariant:
     if 0<=n<sz, elem[n] is element n
     sz <= space_
     if sz < space_ thre is space for (space-sz) doubles after elem[sz-1]
  */

  A alloc;
  size_t sz;
  T *elem;
  size_t space_;

public:
  ///////////////////
  /// Iterator

  // this was super unnecessary and std::iterator is to be deprecated
  /* class iter : std::iterator<std::random_access_iterator_tag, T,
   * std::ptrdiff_t, T *, T &> { */
  class iter {
  private:
    T *curr;

  public:
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

  iter begin() { return elem; }
  const iter begin() const { return elem; }
  iter end() { return elem + sz; }
  const iter end() const { return elem + sz; }

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
    cout << "copy ctor ";
    INFO;

    copy(arg.elem, arg.sz, elem);
  }

  // copy assignment ( 19.2.5 - doesnt make extra space_ )
  // make 1 vector's elements  = to another's
  vector<T> &operator=(const vector &a) {
    INFO;
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
  // - called when an object is initialized from rvalue, eg:
  // T a = std::move(b);  // b being type T
  // f(std::move(a));     // a being type T and f is void f(T t);
  // return a;            // a being type T and in T f();
  vector(vector<T> &&a) : sz{a.sz}, elem{a.elem} {
    // move constructor is used as fuction arg, so is deleted
    // when it goes out of scope
    cout << "move ctor ";
    INFO;
    a.sz = 0;
    a.space_ = 0;
    a.elem = nullptr;
  }

  // move assignment
  vector<T> &operator=(vector<T> &&a) {
    cout << "move assign ";
    INFO;
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
  // because we wouldnt have it's address, just it's value

  T &operator[](int i) {
    INFO;
    return elem[i];
  }

  // we also want to be able to read const element
  // eg.
  const T &operator[](int i) const {
    INFO;
    return elem[i];
  }

  // at is [] but with range checking
  T &at(int i) {
    INFO;
    if (i < 0 || i >= sz) {
      throw std::range_error("out of range");
    }
    return elem[i];
  }

  ///////////////////
  //// Current Size
  size_t capacity() const { return space_; }
  size_t size() const { return sz; }

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
    for (size_t i = 0; i < sz; ++i) {
      alloc.construct(&p[i], elem[i]);
      /* p[i] = elem[i]; */
    }
    for (size_t i = 0; i < sz; ++i) {
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
    for (size_t i = 0; i < sz; ++i) {
      p[i] = elem[i];
    }
    delete[] elem;
    elem = p;
    space_ = newalloc;
  }

  void resize(size_t newsize) {
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
#endif
