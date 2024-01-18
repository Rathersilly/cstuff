// my_array class - with help from LearnCPP ch 23.6
//
// todo - turn this into header
/* #ifndef MY_ARRAY_H */
/* #define MY_ARRAY_H */
/**/
/**/
/* #endif // !MY_ARRAY_H */

#include <cassert>
#include <initializer_list>
#include <iostream>
using namespace std;

template <class T> void print_array(T &t) {
  for (int i = 0; i < t.size(); ++i) {
    cout << t[i] << " ";
  }
  cout << endl;
}

namespace my {
template <class T> class array {
private:
  T *elem;
  int size_;

public:
  int size() { return size_; }
  T &operator[](int i) {
    assert(i >= 0 && i < size_);
    return elem[i];
  }

  void erase() {
    delete[] elem;
    size_ = 0;
    elem = nullptr;
  }
  // resize array, deleting existing elements
  void reallocate(int newsize) {
    erase();
    if (newsize < 0)
      return;

    elem = new T[newsize];
    size_ = newsize;
  }
  void resize(int newsize) {
    T *temp = new T[newsize];
    for (int i = 0; i < size_; ++i) {
      temp[i] = elem[i];
    }
    delete[] elem;
    elem = temp;
    size_ = newsize;
  }

  array() = default;

  array(int s) : size_{s} {
    assert(size_ >= 0);
    if (size_ > 0)
      elem = new T[size_];
  }
  array(std::initializer_list<T> lst) : size_{static_cast<int>(lst.size())} {
    elem = new T[size_];
    std::copy(lst.begin(), lst.end(), elem);
  }
  ~array() { delete[] elem; }

  // Template Info: This must not be <class T> - or will get error:
  // error: declaration of template parameter ‘T’ shadows template parameter
  template <class Y>
  friend std::ostream &operator<<(std::ostream &os, array<Y> &a);
};

// Friend Info:
// this friend function must be defined in the same namespace as the
// declaration. when invoked, the compiler finds it without a scope operator
// by using the scope in the definition
// Reference Info: if arr is not a refernce, it will be a shallow copy of arg,
// if the arg has no copy constructor.  Leads to double free of T* elem.
template <class T> std::ostream &operator<<(std::ostream &os, array<T> &arr) {

  cout << "here";
  for (int i = 0; i < arr.size(); ++i) {
    os << arr.elem[i];
  }
  return os << std::endl;
}
} // namespace my

using my::array;

int main(int argc, char *argv[]) {
  array<int> arr(3);
  array<int> a{1, 2, 3};
  arr[0] = 2;
  std::cout << arr;
  print_array(a);

  return 0;
}
