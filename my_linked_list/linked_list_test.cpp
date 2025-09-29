#include "my_linked_list.h"
#include <algorithm>
#include <iostream>
using namespace std;

template <typename T> void print_list(const myLinkedList<T> &list) {
  for (auto it = list.begin(); it != list.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;
}

void test_list() {
  myLinkedList<int> list;
  static_assert(
      std::is_base_of_v<
          std::forward_iterator_tag,
          myLinkedList<int>::ListIterator::iterator_category>); // ✅ compiles
  for (int i = 0; i < 10; ++i) {
    list.push_back(i);
  }

  print_list(list);
}

int main(int argc, char *argv[]) {
  test_list();
  return 0;
}
