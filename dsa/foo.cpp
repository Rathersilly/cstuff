#include <cassert>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <iostream>
#include <vector>
using namespace fmt;
using namespace std;
template <typename T> struct Node {
  T data;
  Node *next;
};

template <typename T> struct List {
  Node<T> *first = nullptr;
  Node<T> *last = nullptr;

  void push_back(int n) {
    auto foo = new Node<T>{n, nullptr};
    if (first) {
      last->next = foo;
      last = foo;
    } else {
      first = foo;
      last = foo;
    }
  }
  void erase(Node<T> *n) {
    if (n == first) {
      delete first;
      first = nullptr;
      return;
    }
    Node<T> *prev = nullptr;
    for (auto it = first; it; it = it->next) {
      if (it == n) {
        if (it == first) {
          it->next = first;
          delete n;
        } else {
          prev->next = it->next;
          delete n;
        }
      }
      prev = it;
    }
  }
  ~List() {
    if (!first)
      return;
    if (!last)
      delete first;
    auto it = first;
    auto temp = it;
    while (it->next) {
      temp = it->next;
      delete it;
      it = temp;
    }
    delete temp;
  }
};
void print_list(List<int> &list) {
  // if (!list.first)
  //   return;
  for (Node<int> *it = list.first; it; it = it->next) {
    cout << it->data << " ";
  }
  cout << endl;
}

int main(int argc, char *argv[]) {

  List<int> list;
  print_list(list);
  list.push_back(1);
  // list.erase(list.first);
  // print_list(list);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  print_list(list);
  // list.push_back(5);
  // for (auto it = list.first; it != nullptr; it = it->next) {
  //   cout << it->data << " ";
  // }
  // cout << endl;
  // auto it = list.first;
  // list.erase(it);

  // it = list.first;
  // while (it) {
  //   cout << it->data << " ";
  //   it = it->next;
  // }
  // cout << endl;
  // // list.erase(it);
  //
  // while (it) {
  //   cout << it->data << " ";
  //   it = it->next;
  // }
  // cout << endl;
  return 0;
}
template <class T, class Allocator>
myVector<T, Allocator>::myVector(std::initializer_list<T> list)
    : m_size{list.size()}, m_capacity(m_size),
      m_data{allocator.allocate(m_size)} {
  std::copy(list.begin(), list.end(), m_data);
}
