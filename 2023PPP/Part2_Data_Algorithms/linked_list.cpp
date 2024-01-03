// PPP Ch 17 linked list - found out that trying to add a node from a loop
// without allocating memory with new will just reuse the same memory address.
// making your list add the same node again and again.

#include <iostream>
#include <string>
using namespace std;
using std::cout;
using std::endl;

namespace {
string reset = "\033[0m";
string red = "\033[31m";    /* Red */
string green = "\033[32m";  /* Green */
string yellow = "\033[33m"; /* Yellow */
string blue = "\033[34m";   /* Blue */
};                          // namespace
#define INFO cout << reset << "\t" << __PRETTY_FUNCTION__ << endl;

template <typename T> struct Node {

  T data;
  int index;

  Node<T> *prev = nullptr;
  Node<T> *next = nullptr;
};
void inspect_node(Node<int> *n) {
  if (!n) {
    cout << red << "nullptr" << reset << endl;

    return;
  }
  cout << yellow << n->data << endl;
  cout << yellow << n->index << endl;
  cout << yellow << n->prev << endl;
  cout << yellow << n << endl;
  cout << yellow << n->next << endl;
  cout << "---" << reset << endl;
}

template <typename T> class List {
public:
  Node<T> *first = nullptr;
  Node<T> *last = nullptr;
  int sz = 0;
  List() {}
  List(Node<T>) {}

  void add(Node<T> *n) {
    Node<T> *node = n;
    INFO;
    if (!first) {
      cout << "first" << endl;
      node->index = 0;
      first = node;
      last = node;
      /* node->prev = nullptr; */
      /* node->next = nullptr; */
      inspect_node(first);
      inspect_node(node);
      inspect_node(last);
      cout << red << "-------" << reset << endl;
    } else if (first == last) {
      cout << "second" << endl;
      node->index = 1;
      first->next = node;
      node->prev = first;
      last = node;
      last->prev = first;
      inspect_node(first);
      inspect_node(node->prev);
      inspect_node(node);
      inspect_node(node->next);
      inspect_node(last);
      cout << red << "-------" << reset << endl;
    } else {
      cout << "else" << endl;
      node->index = 9;
      node->prev = last;
      last->next = node;
      last = node;
      /* /* node->next = nullptr; */
      /* node->prev = last; */
      /* cout << "---" << endl; */
      /* inspect_node(last); */
      /* last = node; */
      /* inspect_node(node); */
      inspect_node(first);
      inspect_node(node->prev);
      inspect_node(node);
      inspect_node(node->next);
      inspect_node(last);
    }
    sz += 1;
    cout << "Added: " << endl;
    /* print(green); */
  }
  void add(T x) {
    INFO Node<T> node;
    node.data = x;
    this->add(&node);
  }
  void print(string color = reset) {
    INFO Node<T> *curr = first;
    cout << blue << curr->data << reset << endl;
    int i = 0;
    while (curr) {
      cout << color << "(" << i << ") " << curr->data << " -> ";

      curr = curr->next;
      ++i;
      if (i > 20)
        break;
    }
    cout << endl;
    cout << "First: " << first->data << endl;
    cout << "Last: " << last->data << endl;
    cout << "Size: " << sz << endl;
  }
};

int main(int argc, char *argv[]) {
  List<int> list;
  Node<int> node;
  node.data = 123;
  list.add(&node);
  Node<int> node2;
  node2.data = 456;
  list.add(&node2);
  Node<int> node3;
  node3.data = 789;
  list.add(&node3);
  for (int i = 0; i < 3; ++i) {
    // will be deleted when list is destructed.
    // this is necessary - if nn wasnt a pointer, it would go out of scope and
    // the next loop will allocate the same memory address!
    Node<int> *nn = new Node<int>;
    nn->data = i * i;
    list.add(nn);
  }
  list.print();
  return 0;
}
