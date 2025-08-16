// INFO: learning about trees
// TODO: create my_filesystem
// learn the different applications of trees and
// create the right tree for each one.
//
// #include "my_helpers.h"
#include <array>
#include <color_macros.h>
#include <iostream>
#include <set>
#include <typeinfo>

using namespace std;

struct Person {
  string first_name;
  string last_name;
  int id;
  Person(string a, string b, int i) : first_name{a}, last_name{b}, id{i} {}
};

template <typename T, class Compare = std::less<T>> class Tree {
private:
  class Node {
  public:
    T data;
    Node *left = nullptr;
    Node *right = nullptr;

    Node(T value) : data{value} {}
  };

  Node *root = nullptr;

public:
  Tree() {}
  void insert(T arg) {
    if (!root) {
      root = new Node{arg};
    } else {
      // insert in correct place
    }
  }
};
struct CompareByFirstName {
  // dont forget to make the function itself const
  bool operator()(const Person &lhs, const Person &rhs) const {
    return lhs.first_name < rhs.first_name;
  }
};

int main(int argc, char *argv[]) {
  Person alice{"alice", "smith", 1};
  Person bob{"bob", "jones", 2};
  Person charlie{"charlie", "johnson", 3};
  Person dot{"dot", "roberts", 4};
  Person eleanor{"eleanor", "shoemaker", 5};

  Tree<Person, CompareByFirstName> foo;
  // set<Person, CompareByFirstName> foo; // this works just fine
  foo.insert(alice);
  foo.insert(charlie);
  foo.insert(bob);
  foo.insert(dot);
  foo.insert(eleanor);
  for (auto &a : foo) {
    cout << a.first_name;
  }
  return 0;
}
// struct CompareByFirstName {
//   bool operator()(const Person &lhs, const Person &rhs) const {
//     return lhs.first_name < rhs.first_name;
//   }
// };
//
// // Define a tree using a set with custom comparison
// std::set<Person, CompareByFirstName> tree;
//
// int main() {
//   // Insert some people into the tree
//   tree.insert(Person("John", "Doe", 1));
//   tree.insert(Person("Alice", "Smith", 2));
//   tree.insert(Person("Bob", "Johnson", 3));
//   tree.insert(Person("Alice", "Jones", 4));
//
//   // Print the people sorted by first name
//   for (const auto &person : tree) {
//     std::cout << person.first_name << " " << person.last_name
//               << " (ID: " << person.id << ")\n";
//   }
//
//   return 0;
// }
