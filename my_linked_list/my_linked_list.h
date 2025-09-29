#pragma once

#include "color_macros.h"
#include <cstddef>
#include <iostream>
#include <iterator>
#include <list>
using namespace std;

template <std::forward_iterator It> void foo(It first, It last) {
  for (; first != last; ++first) {
  }
}
template <typename T> class myLinkedList {
public:
  class ListIterator;
  class Node {
    T m_data;
    Node *next = nullptr;
    friend class ListIterator;
    friend class myLinkedList;

  public:
    Node(T data) : m_data{data} {}
  };

public:
  class ListIterator {
  public:
    // These do not have to be used - they are compiler hints
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

    Node *m_pointer;

    ListIterator(T *ptr) : m_pointer{ptr} {}
    ListIterator(std::nullptr_t ptr) : m_pointer{ptr} {}
    ListIterator(Node *ptr) : m_pointer{ptr} {}
    ListIterator &operator++() { // pre increment
      m_pointer = m_pointer->next;
      return *this;
    }
    ListIterator operator++(int) { // post increment
      T *temp = m_pointer;
      m_pointer = m_pointer->next;
      return temp;
    }
    bool operator==(const ListIterator &other) {

      return m_pointer == other.m_pointer;
    }
    bool operator!=(const ListIterator &other) {

      return m_pointer != other.m_pointer;
    }
    reference operator*() const { return m_pointer->m_data; }
    // reference operator*() { return m_pointer->m_data; }
    pointer operator->() const { return &m_pointer->m_data; }
  };

  size_t m_size = 0;
  Node *m_first = nullptr;
  Node *m_last = nullptr;

public:
  ListIterator begin() const { return ListIterator{m_first}; }
  ListIterator end() const { return ListIterator{nullptr}; }
  ListIterator end() { return ListIterator{nullptr}; }
  ListIterator begin() { return ListIterator{m_first}; }

  myLinkedList() {}

  void push_back(T data) {
    TRACE_GREEN();
    FTRACE_GREEN();
    TRACE();
    if (m_size == 0) {
      m_first = new Node{data};
      m_last = m_first;

    } else {
      Node *temp = new Node{data};
      m_last->next = temp;
      m_last = temp;
    }
    ++m_size;
  }
};
