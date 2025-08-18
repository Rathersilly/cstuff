#include <iostream>

int foo() // code starts at memory address 0x002717f0
{
  return 5;
}

// overload << to cout address of function
// but can just do cout << &foo - so its academeic

namespace std {
template <typename P> std::ostream &operator<<(std::ostream &os, P (*ptr)()) {
  os << (void *)ptr;
  return os;
}
} // namespace std

int main() {
  std::cout << reinterpret_cast<void *>(foo)
            << '\n'; // Tell C++ to interpret function foo as a void pointer
                     // (implementation-defined behavior)

  std::cout << foo << '\n';  // Tell C++ to interpret function foo as a void
                             // pointer (implementation-defined behavior)
  std::cout << &foo << '\n'; // Tell C++ to interpret function foo as a void
                             // pointer (implementation-defined behavior)
  return 0;
}
