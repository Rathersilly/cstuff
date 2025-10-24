
#include <cstddef>
#include <iostream>
namespace my {

template <typename T> class allocator {
  using allocator_type = allocator;
  using value_type = T;

  T *allocate(size_t n) {
    T *ptr = new T[n];
    return ptr;
  }

  // deallocate is basically wrapper of operator delete
  void deallocate(T *addr, size_t n) { ::operator delete(addr, n); }

  // destroy function is not needed - allocator_traits has a default one
  void destroy(T *p) {
    std::cout << "Calling custom destroy...\n";
    // Perform custom destruction logic here, then call the destructor
    p->~T();
  }
};
} // namespace my
