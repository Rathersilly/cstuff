// LearnCPP ch22 - smart pointers
// TODO - leaving this for later!
#include <algorithm> //std::shuffle
#include <chrono>    // std::chrono::high_resolution_clock / system_clock
#include <color_macros.h>
#include <functional> // std::function
#include <initializer_list>
#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;

template <class T> class SmartPointer {
private:
  T *ptr_;

public:
  SmartPointer(T *ptr) : ptr_{ptr} {}
  /* SmartPointer(SmartPointer<T> smp) : ptr_{smp.ptr_} {} */
  // copy assignment
  /* SmartPointer operator=(SmartPointer &ptr) { */
  /*   ptr_ = ptr; */
  /*   delete ptr; */
  /* } */
  /* // copy ctor */
  /* SmartPointer(SmartPointer &ptr) { */
  /*   ptr_ = ptr; */
  /*   delete ptr; */
  /* } */
  T &operator*() { return *ptr_; }
  T *operator->() { return ptr_; }

  ~SmartPointer() { delete ptr_; }
};

class Foo {
private:
  int x = 2;
  static inline int foo_count = 0;
  int foo_number;

public:
  Foo() {
    foo_number = ++foo_count;
    cout << "Foo created" << endl;
  }
  ~Foo() { cout << "Foo destroyed" << endl; }
};

int main(int argc, char *argv[]) {

  /* SmartPointer<int> *p{new int[10]}; */
  /* SmartPointer<int> *p(new int[10]); */
  /* SmartPointer<int> *p = new int[10]; */
  SmartPointer<Foo> pf{new Foo};
  SmartPointer<Foo> pf2{pf};

  return 0;
}
