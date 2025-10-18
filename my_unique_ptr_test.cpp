// NOTE: my_unique_ptr class
// LearnCPP ch22 etc
//
// TODO: so much
//
//
#include <functional> // std::function
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T> struct my_default_deleter {
  void operator()(T *t) {
    cout << "DELETING" << endl;
    delete t;
  }
};

// function to test using function as deleter
inline void temp_delete() { cout << "DELETING" << endl; }
// to make this function the default:
// template <typename T, typename D = decltype(temp_delete)> class my_unique_ptr
// {

template <typename T, typename D = my_default_deleter<T>> class my_unique_ptr {

private:
  T *curr;
  D deleter;

public:
  my_unique_ptr(T *t = nullptr) : curr{t}, deleter{my_default_deleter<T>{}} {
    PFUN;
    cout << "my_unique_ptr (T *t) ctor" << endl;
  }

  my_unique_ptr(T *t, D d) : curr{t}, deleter{d} {
    PFUN;
    cout << "my_unique_ptr (T *t, D d) ctor" << endl;
  }
  // copying is no bueno. It's my_UNIQUE_ptr
  my_unique_ptr(my_unique_ptr &) = delete;
  my_unique_ptr &operator=(my_unique_ptr &) = delete;

  // Moving is just fine
  my_unique_ptr(my_unique_ptr &&p) : curr{p.curr} {}
  my_unique_ptr &operator=(my_unique_ptr &&p) {
    curr = p.curr;
    p.curr = nullptr;
    return *this;
  }

  T operator*() { return *curr; }
  T *operator->() { return curr; }

  T *get() { return curr; }

  ~my_unique_ptr() { deleter(curr); }
};
