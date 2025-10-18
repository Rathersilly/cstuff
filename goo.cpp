#include "object_pool.h"
#include <cstdint>
#include <fmt/base.h>
#include <iostream>
#include <memory>

using namespace std;
using namespace fmt;

class Texture {
public:
  int a;
  int b;
  Texture() {}
  Texture(int aa, int bb) : a{aa}, b{bb} { print("ctr\n"); }
  Texture(Texture const &t) {
    print("copy ctr\n");
    a = t.a;
    b = t.b;
  }
  Texture &operator=(const Texture &t) {
    print("copy ass\n");

    this->a = t.a;
    this->b = t.b;

    return *this;
  }
  Texture(Texture &&t) { print("move ctr\n"); }
  Texture &operator=(Texture &&t) {
    print("move ass\n");
    return *this;
  }
};
template <class T> std::remove_reference_t<T> &&mv(T &other) {
  return static_cast<std::remove_reference<T> &&>(other);
}

void delete_texture(Texture &t) { printf("deleting texture\n"); }

int main() {
  // unique_ptr<Texture, decltype(delete_texture)> ptr;
  Texture a{1, 2};
  Texture b{a};
  Texture c;
  c = a;
  Texture d = std::move(a);
  c = std::move(b);
  d = std::move(c);
  fmt::print("{}\n", a.a);
  fmt::print("{}\n", b.a);
  fmt::print("{}\n", c.a);
  fmt::print("{}\n", d.a);
}
