#include "my_deque.h"
#include <color_macros.h>
#include <iomanip>
#include <iostream>
using namespace std;

void test_push_front(myDeque<int> &deq) {}

void test_pop_back(myDeque<int> &deq) {
  TRACE_BLUE();

  cout << deq.front() << " " << deq.back() << endl;
  deq.pop_back();
  cout << deq.front() << " " << deq.back() << endl;
  deq.pop_back();
  cout << deq.front() << " " << deq.back() << endl;
  deq.pop_back();
}
void test_pop_front(myDeque<int> &deq) {
  TRACE_BLUE();

  cout << deq.f_index << " " << deq.front() << " " << deq.b_index << " "
       << deq.back() << endl;
  deq.pop_front();
  cout << deq.f_index << " " << deq.front() << " " << deq.b_index << " "
       << deq.back() << endl;
  deq.pop_front();
  cout << deq.f_index << " " << deq.front() << " " << deq.b_index << " "
       << deq.back() << endl;
  deq.pop_front();
  cout << deq.f_index << " " << deq.front() << " " << deq.b_index << " "
       << deq.back() << endl;
}

int main(int argc, char *argv[]) {
  myDeque<int> deq;
  cout << "deq.f_index" << setw(14) << "deq.front()" << setw(14)
       << "deq.b_index" << setw(14) << "deq.back()" << endl;
  for (int i = 0; i < 8; ++i) {
    deq.push_back(i);
    cout << deq.f_index << setw(14) << deq.front() << setw(14) << deq.b_index
         << setw(14) << deq.back() << endl;
    deq.print();
  }

  deq.print();
  // for (int i = 8; i < 30; ++i) {
  //   deq.push_back(i);
  //   cout << deq.back() << " " << deq.b_block << " " << deq.b_index << " ";
  //   cout << deq.block_map[deq.b_block]->at(deq.b_index) << endl;
  // }
  // deq.print();
  // test_pop_back(deq);
  // test_pop_front(deq);
  // test_push_front(deq);
  return 0;
}
