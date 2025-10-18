// TODO: show trailing return type and when it might be useful
// - this was a get/set demo but can be cannibalized
// - https://google.github.io/styleguide/cppguide.html#Functions
#include <iostream>
#include <string>
#include <vector>
#define INFO std::cout << "\t" << __PRETTY_FUNCTION__ << std::endl;
typedef int X;
using namespace std;

// from
// https://stackoverflow.com/questions/737409/are-get-and-set-functions-popular-with-c-programmers
class Foo {
public:
  std::string Bar() const { return bar; }
  void Bar(const std::string &bar) { this->bar = bar; }

private:
  std::string bar;
};

// Identity oriented - I think I like this one the best but holy shit how does
// this overload work?
// 					 - like how does the right function get
// called?
class Foo2 {
  X x_;

public:
  X &x() {
    INFO;
    return x_;
  }
  const X &x() const {
    INFO;
    return x_;
  }
};
// The above but with trailing return function style:
class Foo2_5 {
private:
  X x_;

public:
  auto x() -> X & { return x_; }
  auto x() const -> const X & { return x_; }
};
// Value oriented
class Foo3 {
  X x_;

public:
  X x() const { return x_; }
  void x(X x) { x_ = std::move(x); } //
};

int main(int argc, char *argv[]) {
  Foo2 f;
  f.x() = 5;
  cout << f.x() << endl;
}
