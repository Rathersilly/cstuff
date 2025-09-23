#pragma once

#include <color_macros.h>
#include <cstddef>
#include <filesystem>
#include <initializer_list>
#include <iostream>
#include <string>
using namespace std;

template <typename T> class myVector {
protected:
  size_t m_size;
  size_t m_capacity;
  static constexpr size_t m_reserve_factor =
      2; // increase capacity by this factor upon push_back
  T *m_data;

  void data_resize(size_t new_size) {}

public:
  class myIterator;
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

template <typename T> class myVector<T>::myIterator {

public:
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
template <typename T> myVector<T>::myVector() : m_size{0}, m_data{nullptr} {
  TRACE_GREEN();
}
template <typename T> myVector<T>::~myVector() {
  TRACE_RED();
  delete[] m_data;
}

template <typename T>
myVector<T>::myVector(size_t s) : m_size{s}, m_capacity{s} {
  TRACE_GREEN();
  m_data = new T[s];
  for (int i = 0; i < s; ++i) {
    m_data[i] = T{};
  }
}
template <typename T>
myVector<T>::myVector(std::initializer_list<T> list)
    : m_size{list.size()}, m_data{new T[m_size]} {
  cout << "initializer_list constructor: ";
  TRACE_GREEN();
  std::copy(list.begin(), list.end(), m_data);
}

template <typename T>
myVector<T>::myVector(const myVector &a)
    : m_size{a.size()}, m_data{new T[m_size]} {
  cout << "copy constructor: ";
  FTRACE_GREEN();
  copy(a.m_data, a.m_data + m_size, m_data);
}

template <typename T> myVector<T> &myVector<T>::operator=(myVector &&a) {
  cout << "move assignment: ";
  FTRACE_GREEN();
  delete[] m_data;
  m_size = a.m_size;
  m_data = a.m_data;
  a.m_size = 0;
  a.m_data = nullptr;
  return *this;
}

template <typename T>
myVector<T>::myVector(myVector &&a) : m_size{a.size()}, m_data{a.m_data} {
  cout << "move constructor: ";
  FTRACE_GREEN();
  a.m_size = 0;
  a.m_data = nullptr;
}

// copy assignment
template <typename T> myVector<T> &myVector<T>::operator=(const myVector &a) {
  cout << "copy assignment: ";
  FTRACE_GREEN();
  delete[] m_data;
  m_size = a.size();
  m_data = new T[m_size];
  copy(a.m_data, a.m_data + m_size, m_data);
  return *this;
}

template <typename T> void myVector<T>::reserve(size_t new_capacity) {
  if (new_capacity <= m_capacity) {
    return;
  }
  T *new_data = new T[new_capacity];
  for (int i = 0; i < m_size; ++i) {
    new_data[i] = m_data[i];
  }
  delete[] m_data;
  m_data = new_data;
  m_capacity = new_capacity;
}

template <typename T> void myVector<T>::resize(size_t new_size) {
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
      new (&m_data[i]) T{};
    }
  }
  m_size = new_size;
}

template <typename T> void myVector<T>::push_back(T item) {
  if (m_size == m_capacity) {
    reserve(m_size * m_reserve_factor);
  }

  m_data[m_size] = std::move(item);
  ++m_size;
}
template <typename T> void myVector<T>::emplace_back(T &&item) {
  if (m_size == m_capacity) {
    reserve(m_size * m_reserve_factor);
  }

  m_data[m_size] = std::move(item);
  ++m_size;
}
