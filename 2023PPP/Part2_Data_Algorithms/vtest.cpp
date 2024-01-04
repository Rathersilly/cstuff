#include "vtest.h"
template <typename T> vector<T>::vector() : sz{0}, elem{nullptr}, space{0} {
  INFO;
}

template <typename T> Foo<T>::Foo() {}
template class Foo<int>;
