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
template <typename T> class vector {
  /* invariant:
     if 0<=n<sz, elem[n] is element n
     sz <= space
     if sz < space thre is space for (space-sz) doubles after elem[sz-1]
  */

public:
  size_t sz;
  T *elem;
  size_t space;

  vector(); // 1. default constructor
            //
            //
};

template <typename T> class Foo {
public:
  size_t sz;
  /* T *elem; */
  size_t space;

  Foo(); // 1. default constructor
};

template <typename T> void copy(T *from, int sz, T *to);
template <typename T> void print_vector(const vector<T> &v);
#endif
