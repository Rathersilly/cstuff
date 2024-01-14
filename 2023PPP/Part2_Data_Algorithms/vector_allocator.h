#ifndef VECTOR_ALLOCATOR_H
#define VECTOR_ALLOCATOR_H
#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
#include <iostream>
using std::cout;
using std::endl;

namespace my {
template <typename T> class allocator {
public:
  T *allocate(int n) {
    INFO;
    T *p = new T[n];
    return p;
  }
  void deallocate(T *p, int n) { INFO; }

  void construct(T *p, const T &v) {
    INFO;
    *p = v;
  }

  void destroy(T *p) {
    INFO;
    *p = T();
  }
};

} // namespace my
#endif
