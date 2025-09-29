#pragma once

#include <color_macros.h>
#include <cstddef>
#include <filesystem>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
using namespace std;
// TODO: figure out how to split this file and have them still
// be recognized by clangd
// can't define them in a cpp file because need template to see types
// unless you explicitly define them
// altertative is using a .tpp file - but clangd hates that
// you #include "my_vector.tpp" at the BOTTOM of this file

template <class T, class Allocator = std::allocator<T>> class myVector {
protected:
  size_t m_size;
  size_t m_capacity;
  static constexpr size_t m_reserve_factor =
      2; // increase capacity by this factor upon push_back
  T *m_data;
  Allocator allocator;

  void data_resize(size_t new_size) {}

public:
  class myIterator;
  class myBackInserter;
  myIterator begin() { return myIterator(m_data); }
  myIterator end() { return myIterator(m_data + m_size); }

  // todo initialize data
  myVector();
  ~myVector();
  myVector(size_t s);
  myVector(std::initializer_list<T> list);

  myVector(const myVector &a);

  myVector &operator=(myVector &&a);

  myVector(myVector &&a);

  // copy assignment
  myVector &operator=(const myVector &a);

  size_t size() const { return m_size; }
  size_t capacity() { return m_capacity; }
  void reserve(size_t new_capacity);
  void resize(size_t new_size);
  void push_back(T item);
  void emplace_back(T &&item);

  virtual T &operator[](size_t index) { return m_data[index]; }
  virtual const T &operator[](size_t index) const { return m_data[index]; }
};

// Iterator
template <class T, class Allocator> class myVector<T, Allocator>::myIterator {

public:
  using iterator_category = std::contiguous_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T &;

  T *m_pointer;

  myIterator(T *ptr) {
    FTRACE();
    m_pointer = ptr;
  }
  myIterator(T &addr) {
    FTRACE();
    m_pointer = &addr;
  }

  T &operator*() { return *m_pointer; }
  const T &operator*() const { return *m_pointer; }
  // pre-increment
  myIterator &operator++() {
    ++m_pointer;
    return *this;
  }
  // post-increment
  myIterator operator++(int) {
    myIterator temp = *this;
    ++m_pointer;
    return temp;
  }
  friend myIterator operator-(const myIterator &it, int i) {
    return myIterator(it.m_pointer - i);
  }
  friend myIterator operator+(int i, const myIterator &it) {
    return myIterator(i + it.m_pointer);
  }
  friend myIterator operator+(const myIterator &it, int i) {
    return myIterator(it.m_pointer + i);
  }
  friend ptrdiff_t operator-(const myIterator &it, const myIterator &other_it) {
    return myIterator(it.m_pointer - other_it.m_pointer);
  }
};

// todo initialize data

template <class T, class Allocator>
myVector<T, Allocator>::myVector() : m_size{0}, m_data{nullptr} {
  TRACE_GREEN();
}
template <class T, class Allocator> myVector<T, Allocator>::~myVector() {
  TRACE_RED();
  delete[] m_data;
}

template <class T, class Allocator>
myVector<T, Allocator>::myVector(size_t s) : m_size{s}, m_capacity{s} {
  TRACE_GREEN();
  m_data = allocator.allocate(m_size);
  for (int i = 0; i < s; ++i) {
    m_data[i] = T{};
  }
}
template <class T, class Allocator>
myVector<T, Allocator>::myVector(std::initializer_list<T> list)
    : m_size{list.size()}, m_capacity(m_size),
      m_data{allocator.allocate(m_size)} {
  cout << "initializer_list constructor: ";
  std::copy(list.begin(), list.end(), m_data);
}

template <class T, class Allocator>
myVector<T, Allocator>::myVector(const myVector &a)
    : m_size{a.size()}, m_data{allocator.allocate(m_size)} {
  cout << "copy constructor: ";
  FTRACE_GREEN();
  copy(a.m_data, a.m_data + m_size, m_data);
}
template <class T, class Allocator>
class myVector<T, Allocator>::myBackInserter {
  myVector *v;

public:
  myBackInserter(myVector *vec) : v{vec} {}
  myBackInserter operator=(T item) {
    v->push_back(item);
    return *this;
  }
};
// myVector Implementation
template <class T, class Allocator>
myVector<T, Allocator> &myVector<T, Allocator>::operator=(myVector &&a) {
  cout << "move assignment: ";
  FTRACE_GREEN();
  delete[] m_data;
  m_size = a.m_size;
  m_data = a.m_data;
  a.m_size = 0;
  a.m_data = nullptr;
  return *this;
}

template <class T, class Allocator>
myVector<T, Allocator>::myVector(myVector &&a)
    : m_size{a.size()}, m_data{a.m_data} {
  cout << "move constructor: ";
  FTRACE_GREEN();
  a.m_size = 0;
  a.m_data = nullptr;
}

// copy assignment
template <class T, class Allocator>
myVector<T, Allocator> &myVector<T, Allocator>::operator=(const myVector &a) {
  cout << "copy assignment: ";
  FTRACE_GREEN();
  delete[] m_data;
  m_size = a.size();
  m_data = allocator.allocate(m_size);
  copy(a.m_data, a.m_data + m_size, m_data);
  return *this;
}

template <class T, class Allocator>
void myVector<T, Allocator>::reserve(size_t new_capacity) {
  if (new_capacity <= m_capacity) {
    return;
  }
  T *new_data = allocator.allocate(new_capacity);
  for (int i = 0; i < m_size; ++i) {
    new_data[i] = m_data[i];
  }
  delete[] m_data;
  m_data = new_data;
  m_capacity = new_capacity;
}

template <class T, class Allocator>
void myVector<T, Allocator>::resize(size_t new_size) {
  if (new_size == m_size) {
    return;
  } else if (new_size < m_size) {
    for (size_t i = new_size; i < m_size; ++i) {
      m_data[i].~T();
    }
  } else { // new_size > m_size
    if (new_size > m_capacity) {
      reserve(new_size);
    }
    for (int i = m_size; i < new_size; ++i) {
      // TODO: allocator.construct?
      new (&m_data[i]) T{};
    }
  }
  m_size = new_size;
}

template <class T, class Allocator>
void myVector<T, Allocator>::push_back(T item) {
  if (m_size == m_capacity) {
    reserve(m_size * m_reserve_factor);
  }

  m_data[m_size] = std::move(item);
  ++m_size;
}
template <class T, class Allocator>
void myVector<T, Allocator>::emplace_back(T &&item) {
  if (m_size == m_capacity) {
    reserve(m_size * m_reserve_factor);
  }

  m_data[m_size] = std::move(item);
  ++m_size;
}
