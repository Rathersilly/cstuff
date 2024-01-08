#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
#include <iostream>
using std::cout;
using std::endl;
template <typename T> class allocator {
  public:
  T *allocate(int n) {
    INFO;
    T* p = new T[n];
    return p;
  }
  void deallocate(T *p, int n){
    INFO;
  }

  void construct(T *p, const T &v) {
    INFO;
    *p = v;
  }

    
  void destroy(T *p) {
    INFO;
    *p = T();
  }

};

