#include "my_vector.h"

static int foos = 0;
static int goos = 0;
class Foo {
public:
  int *elem;
  Foo() {
    cout << GREEN << "constructing a Foo" << RESET << endl;
    ++foos;
    elem = new int[3];
  }
  ~Foo() {

    delete[] elem;
    --foos;
    cout << RED << "destructing a Foo" << RESET << endl;
  }
};
class Goo : public Foo {
public:
  Foo *elem;
  Goo() {
    cout << GREEN << "constructing a Goo" << RESET << endl;
    elem = new Foo[3];
    ++goos;
  }
  ~Goo() {

    delete[] elem;
    cout << RED << "destructing a Goo" << RESET << endl;
    --goos;
  }
};

void count() {
  cout << RESET << "foos: " << foos << endl;
  cout << "goos: " << goos << RESET << endl;
}

void make_stuff() {
  Goo g;
  count();
}
int main(int argc, char *argv[]) {

  // make a Goo, which makes 3 Foos
  // can mess with the destructors to see what happens in valgrind
  make_stuff();
  count();
  vector<Foo> f{3};
  count();
  vector<Goo> g{3};
  count();
  return 0;
}
