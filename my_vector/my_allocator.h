#pragma once
#include <cstddef>
#include <iostream>

template <typename T> struct MyAllocator {
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  T *allocate(size_t n) {
    return static_cast<T *>(::operator new(n * sizeof(T)));
  }

  void deallocate(T *addr, size_t n) { ::operator delete(addr, n * sizeof(T)); }

  // destroy function is not needed - allocator_traits has a default one
  void destroy(T *p) {
    std::cout << "Calling custom destroy...\n";
    // Perform custom destruction logic here, then call the destructor
    p->~T();
  }
};
