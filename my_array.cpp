// my::array class
//
#include <iostream>
#include <typeinfo>

using namespace std;

namespace my {

template <typename T> class array {
private:
  size_t size_;
  T *elem;

public:
  array() {}
  array(size_t s) : size_{s} { elem = new int[s]; }
  array(array &other) : size_{other.size()}, elem{new T[size_]} {
    for (int i = 0; i < size_; ++i)
      elem[i] = other.elem[i];
  }
  // TODO:check that return values agree or are correct
  array operator=(array &other) {
    size_ = {other.size()};
    elem = new T[size_];
    for (int i = 0; i < size_; ++i)
      elem[i] = other.elem[i];
    return this;
  }
  // check the responsibilities of move ctor - same as copy?
  array(array &&other) {
    size_ = {other.size()};
    elem = new T[size_];
    for (int i = 0; i < size_; ++i)
      elem[i] = other.elem[i];
  }

  ~array() { delete[] elem; }
  T &operator[](size_t n) { return elem[n]; }

  size_t size() { return size_; }
};
} // namespace my

int main(int argc, char *argv[]) {
  my::array<int> foo(5);
  my::array<int> goo(foo);
  foo[2] = 3;
  cout << foo[2];
  cout << goo[2];
  foo[2] = 5;
  cout << foo[2];
  cout << goo[2];
  ;
  ;
  return 0;
}
