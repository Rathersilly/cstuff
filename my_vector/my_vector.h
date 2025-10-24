#pragma once

#include "my_allocator.h"
// #include "my_log.h"
#include <color_macros.h>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>

using namespace std;
// TODO: figure out how to split this file and have them still
// be recognized by clangd
// can't define them in a cpp file because need template to see types
// unless you explicitly define them
// altertative is using a .tpp file - but clangd hates that
// you #include "my_vector.tpp" at the BOTTOM of this file

// TODO: emplace_back
// reverse iterator
// make compatible with std algos
// make logging cleaner - use spdlog i guess
namespace debug {
static bool verbosity = true;
}
template <class T, class Allocator = std::allocator<T>> class myVector {
public:
  using value_type = T;

  class myIterator;
  myIterator begin() { return myIterator(m_data); }
  myIterator end() { return myIterator(m_data + m_size); }
  const myIterator begin() const { return myIterator(m_data); }
  const myIterator end() const { return myIterator(m_data + m_size); }

  // Constructors
  myVector();
  myVector(size_t s);
  myVector(std::initializer_list<T> list);
  myVector(const myVector &a);
  myVector &operator=(myVector &&a); // move assignment
  myVector(myVector &&a);
  myVector &operator=(const myVector &a); // copy assignment
  ~myVector();

  // Accessors
  const size_t size() const { return m_size; }
  const size_t capacity() const { return m_capacity; }
  size_t reserve_factor() { return m_reserve_factor; }

  virtual T &operator[](size_t index) { return m_data[index]; }
  virtual const T &operator[](size_t index) const { return m_data[index]; }

  // Member Functions
  void reserve(size_t new_capacity);
  void resize(size_t new_size);
  void push_back(T item);
  // void emplace_back(T &&item); // needs Args

protected:
  size_t m_size = 0;
  size_t m_capacity = 0;
  static constexpr size_t m_reserve_factor =
      2; // reserve increases capacity by this factor
  T *m_data;
  Allocator allocator;

  void data_resize(size_t new_size) {}
};

// Constructors
template <class T, class Allocator>
myVector<T, Allocator>::myVector() : m_size{0}, m_capacity(0), m_data{nullptr} {
  if (debug::verbosity) {
    cout << "default constructor: ";
    FTRACE_GREEN();
  }
}

template <class T, class Allocator>
myVector<T, Allocator>::myVector(size_t s) : m_size{s}, m_capacity{s} {
  if (debug::verbosity) {
    cout << "size & default init constructor: ";
    TRACE_GREEN();
  }

  m_data = allocator.allocate(m_size);
  for (size_t i = 0; i < s; ++i) {
    m_data[i] = T{};
  }
}

template <class T, class Allocator>
myVector<T, Allocator>::myVector(std::initializer_list<T> list)
    : m_size{list.size()}, m_capacity(m_size),
      m_data{allocator.allocate(m_size)} {
  if (debug::verbosity) {
    cout << "initializer_list constructor: ";
    FTRACE_GREEN();
  }
  // std::copy(list.begin(), list.end(), m_data);
  auto current = m_data;
  for (const T &item : list) {
    std::allocator_traits<Allocator>::construct(allocator, current, item);
    ++current;
  }
}

template <class T, class Allocator>
myVector<T, Allocator>::myVector(const myVector &a)
    : m_size{a.m_size}, m_capacity{m_size}, m_data{allocator.allocate(m_size)} {
  if (debug::verbosity) {
    cout << "copy constructor: ";
    FTRACE_GREEN();
  }
  copy(a.m_data, a.m_data + m_size, m_data);
}

template <class T, class Allocator>
myVector<T, Allocator>::myVector(myVector &&a)
    : m_size{a.m_size}, m_capacity{a.m_size}, m_data{a.m_data} {
  if (debug::verbosity) {
    cout << "move constructor: ";
    FTRACE_GREEN();
  }
  a.m_size = 0;
  a.m_capacity = 0;
  a.m_data = nullptr;
}

// copy assignment
template <class T, class Allocator>
myVector<T, Allocator> &myVector<T, Allocator>::operator=(const myVector &a) {
  if (debug::verbosity) {
    cout << "copy assignment: ";
    FTRACE_GREEN();
  }
  delete[] m_data;
  m_size = a.m_size;
  m_capacity = a.m_size;
  m_data = allocator.allocate(m_size);
  copy(a.m_data, a.m_data + m_size, m_data);
  return *this;
}

// move assignment
template <class T, class Allocator>
myVector<T, Allocator> &myVector<T, Allocator>::operator=(myVector &&a) {
  if (debug::verbosity) {
    cout << "move assignment: ";
    FTRACE_GREEN();
  }
  m_size = a.m_size;
  m_capacity = a.m_capacity;
  m_data = a.m_data;
  a.m_size = 0;
  a.m_data = nullptr;
  return *this;
}

// Destructor
template <class T, class Allocator> myVector<T, Allocator>::~myVector() {
  if (debug::verbosity) {
    cout << "destructor: ";
    FTRACE_RED();
  }

  // destroy each item
  for (size_t i = 0; i < m_size; ++i) {
    std::allocator_traits<Allocator>::destroy(allocator, m_data + i);
  }

  allocator.deallocate(m_data, m_capacity);
}

template <class T, class Allocator>
void myVector<T, Allocator>::reserve(size_t new_capacity) {
  if (new_capacity <= m_capacity) {
    return;
  }
  T *new_data = allocator.allocate(new_capacity);
  for (size_t i = 0; i < m_size; ++i) {
    new_data[i] = std::move(m_data[i]);
  }
  allocator.deallocate(m_data, m_capacity);
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
    for (size_t i = m_size; i < new_size; ++i) {
      // TODO: allocator.construct?
      new (&m_data[i]) T{};
    }
  }
  m_size = new_size;
}

template <class T, class Allocator>
void myVector<T, Allocator>::push_back(T item) {
  if (m_size == m_capacity) {
    reserve(std::max((size_t)1, m_size * m_reserve_factor));
  }

  m_data[m_size] = std::move(item);
  ++m_size;
}

// lol thats not what emplace does - it forwards args
// template <class T, class Allocator>
// void myVector<T, Allocator>::emplace_back(T &&item) {
//   if (m_size == m_capacity) {
//     reserve(m_size * m_reserve_factor);
//   }
//
//   m_data[m_size] = std::move(item);
//   ++m_size;
// }

// Iterator (contiguous)
// TODO: this can be genericized for diff containers (see backinserter below)
template <class T, class Allocator> class myVector<T, Allocator>::myIterator {

public:
  using iterator_category = std::contiguous_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T &;

  T *m_pointer;

  myIterator(T *ptr) { m_pointer = ptr; }
  myIterator(T &addr) { m_pointer = &addr; }

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
  friend bool operator==(const myIterator &it, const myIterator &other_it) {
    return it.m_pointer == other_it.m_pointer;
  }
};

// Iterator (Back Inserter)
// TODO:- could have container as template also - same with other iterators?
// also relearn traits/concepts for these
// template <class T, class Allocator>
template <class Container> class myBackInserter {
  using iterator_category = std::output_iterator_tag;
  using value_type = void;
  using difference_type = std::ptrdiff_t;
  using pointer = void;
  using reference = void;
  using container_type = Container;

public:
  myBackInserter(Container &c) : container{&c} {}

  myBackInserter operator=(const typename Container::value_type item) {
    container->push_back(item);
    return *this;
  }
  // Dereference operator: no op (returns *this to allow assignment chaining)
  // this also makes (*it = value) work like (it = value)
  myBackInserter &operator*() { return *this; }

  // Pre-increment operator: no op
  myBackInserter &operator++() { return *this; }

  // Post-increment operator: no op
  myBackInserter operator++(Container::value_type) { return *this; }

private:
  Container *container;
};
// Iterator (InputIterator)
// template <class T, class Allocator> class myVector<T,
// Allocator>::myInputIterator {
//   using iterator_category = std::input_iterator_tag;
//   using value_type = const T;
//   using difference_type = std::ptrdiff_t;
//   using pointer = T *;
//   using reference = T &;
// };
