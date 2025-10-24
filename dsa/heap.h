// TODO: wrap head around trees
#include <algorithm>
#include <iterator>

template <class T, class Compare = std::less<>> class ListHeap {
  class Node {
    Node *parent;
    Node *left;
    Node *right;
    T value;
  };

public:
  Node *head = nullptr;

  ListHeap() {}
  void insert(T item) {
    // find first empty spot
    Node *prev = nullptr;
    Node *curr = head;
    while (curr) {
      if (curr->right) {
        curr = curr->left
      }
      curr = head->left
    }
    // found first empty node
  }
};
