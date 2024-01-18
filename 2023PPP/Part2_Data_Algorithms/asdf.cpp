
#include <iostream>
using namespace std;

class Foo {
public:
  int num_;
  Foo() {}
  Foo(int num) : num_{num} {}
};
class Bar : public Foo {
public:
  /* Bar(int n) : Foo(n) {} */
};

int main(int argc, char *argv[]) {
  Bar b{3};
  cout << b.num_;
  return 0;
}
