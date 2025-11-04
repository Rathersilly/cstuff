#include <algorithm>
#include <cassert>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <iostream>
#include <numeric>
#include <random>
#include <stack>
#include <vector>
using namespace fmt;
using namespace std;
std::mt19937 mt(std::random_device{}());

template <typename T> class StackList {
public:
  struct Node {
    T data;
    Node *next = nullptr;
  };
  void push(T data) {
    auto node = new Node(data);
    node->next = m_top;
    m_top = node;
  }
  T pop() {
    if (m_top == m_bottom)
      return -1;
    if (m_top != m_bottom)
      m_top = m_top->next;
    return m_top->data;
  }

private:
  Node *m_bottom = Node();
  Node *m_top = m_bottom;
};

int main(int argc, char *argv[]) {

  std::stack<int> s;
  s.push(1);
  print("{}", s.top());
  s.pop();
  print("{}", s.top());
  s.pop();
  print("{}", s.top());
}
