#include <iostream>
#include <vector>

int main() {
  std::vector<int> v;
  v.reserve(1000);

  std::cout << "Before shrink: " << static_cast<const void *>(v.data())
            << " capacity=" << v.capacity() << "\n";

  v.resize(10);
  v.shrink_to_fit();

  std::cout << "After shrink:  " << static_cast<const void *>(v.data())
            << " capacity=" << v.capacity() << "\n";

  v.reserve(1000);

  std::cout << "Before shrink: " << v.data() << " capacity=" << v.capacity()
            << "\n";

  v.resize(10);
  v.shrink_to_fit();

  std::cout << "After shrink:  " << v.data() << " capacity=" << v.capacity()
            << "\n";

  char str[] = "hello";
  std::cout << "no cast: " << str
            << "\nwith cast: " << static_cast<const void *>(str) << "\n";
  std::cout << "no cast: " << str << "\nwith cast: " << static_cast<void *>(str)
            << "\n";
}
