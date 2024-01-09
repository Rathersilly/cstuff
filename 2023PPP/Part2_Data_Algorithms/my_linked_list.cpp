// Ch20 - basic doubly linked list with iterator

#include <color_macros.h>
#include <iostream>
#include <string>
#include <utility>
using namespace std;
template <class T> class MyList {
private:
  struct Node {
    Node *prev = nullptr;
    Node *next = nullptr;
    T data;
    Node(T t) : data{t} {};
    Node(){};
  };

  Node *start_ = nullptr;
  Node *end_ = nullptr;

public:
  class iter;
  iter begin() { return iter(start_); }
  iter end() { return iter(end_); }
  MyList() {
    /* start_ = new Node; */
    /* start_->prev = start_; */
  }
  void push_back(T t) {
    Node *n = new Node(t);
    if (!start_) {
      end_ = new Node;
      n->data = t;
      n->next = end_;
      end_->prev = n;
      start_ = n;
      return;
    }
    n = end_; // handles n->prev
    end_ = new Node;
    n->next = end_;
    n->data = t;

    end_->prev = n;
  }
};
template <class T> class MyList<T>::iter {
  Node *curr;

public:
  iter(Node *n) : curr(n) {}
  T &operator*() { return curr->data; }
  bool exists() { return (curr != nullptr); }
  bool operator==(iter i) { return curr == i.curr; }
  bool operator!=(iter i) { return curr != i.curr; }
  iter operator++() {
    curr = curr->next;
    return *this;
  }
  iter operator--() {
    curr = curr->prev;
    return *this;
  }
};

template <class T> void print_list(MyList<T> list) {
  for (auto a = list.begin(); a != list.end(); a = ++a) {
    cout << *a << " ";
  }
  cout << endl;
}
template <class T> void print_list_reversed(MyList<T> list) {
  if (list.begin() == list.end())
    return;
  for (auto a = --list.end(); a.exists(); --a) {
    cout << *a << " ";
  }
  cout << endl;
}

int main(int argc, char *argv[]) {
  MyList<int> foo;
  /* for (auto i : 10) { */
  for (int i = 0; i < 10; ++i) {

    foo.push_back(i);
  }
  cout << "print_list" << endl;
  print_list(foo);
  print_list_reversed(foo);

  return 0;
}
