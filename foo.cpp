#include <iostream>
#include <memory>
using namespace std;
void deleter(int *i) {}

struct Foo {};
struct D // deleter
{
  D(){};
  D(const D &) { std::cout << "D copy ctor\n"; }
  D(D &) { std::cout << "D non-const copy ctor\n"; }
  D(D &&) { std::cout << "D move ctor \n"; }
  void operator()(Foo *p) const {
    std::cout << "D is deleting a Foo\n";
    delete p;
  };
};
struct E {
  E() {}
  void operator()() {}
};

int main(int argc, char *argv[]) {
  int a;
  int *b;
  // auto p = unique_ptr<int, decltype(deleter)>(a, deleter);
  // auto q = unique_ptr<int, decltype(deleter)>(a, deleter);
  // auto r = unique_ptr<int, E>(a, deleter);
  D d;
  Foo *f;
  {
    auto s = unique_ptr<Foo, D>(f, d);
    auto t = make_unique<int>();
  }
  return 0;
}
