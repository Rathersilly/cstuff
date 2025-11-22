// TODO: check 2023doc and the linked stack overflow post
// finally grokking move/rvalues
// basically rvalues are temporary values that only last during the current
// expression
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
class Foo {
public:
  int x;
  Foo(int xx = 5) : x{xx} {}
};
class Goo { // class that needs move
public:
  int *elem;
  int size_;
  Goo(int size = 5) : size_{size} {
    elem = new int[size_];
    for (int i = 0; i < size_; ++i)
      elem[i] = i;
  }
};

int main(int argc, char *argv[]) {
  Foo foo{8};
  Foo foo2;
  int a = 2;
  int b = a;
  cout << a << endl; // 2
  cout << b << endl; // 2

  // this does same as int c = a.
  // a is unaffected
  int c = static_cast<int &&>(a);
  cout << a << endl; // 2
  cout << c << endl; // 2
  a = 7;
  cout << a << endl; // 7
  cout << c << endl; // 2
  foo2 = static_cast<Foo &&>(foo);
  cout << foo.x;
  cout << foo2.x;

  // these are all the same - because they have no
  // custom move/destruction
  // TODO: double check my_vector to see how it works -
  // make minimal example here
  Goo goo(5);    // goo has int* elem
  Goo goo2(goo); // goo2's elem points to goo's
  Goo goo3 = static_cast<Goo &&>(goo);
  Goo goo4 = std::move(goo);
  cout << goo.elem[2];  // 2
  cout << goo2.elem[2]; // 2
  cout << goo3.elem[2]; // 2
  cout << "\n*****" << endl;
  goo2.elem[2] = 7;
  goo3.elem[2] = 9;
  cout << goo.elem[2];  // 9
  cout << goo2.elem[2]; // 9
  cout << goo3.elem[2]; // 9
  goo4.elem[2] = 8;
  cout << goo.elem[2];  // 8
  cout << goo2.elem[2]; // 8
  cout << goo3.elem[2]; // 8
  std::string str = "Salut";
  std::vector<std::string> v;

  // examples from cppref - std::move
  // uses the push_back(const T&) overload, which means
  // we'll incur the cost of copying str
  v.push_back(str);
  std::cout << "\nAfter copy, str is " << std::quoted(str) << '\n';

  // uses the rvalue reference push_back(T&&) overload,
  // which means no strings will be copied; instead, the contents
  // of str will be moved into the vector. This is less
  // expensive, but also means str might now be empty.
  v.push_back(std::move(str));
  std::cout << "After move, str is " << std::quoted(str) << '\n';

  std::cout << "The contents of the vector are { " << std::quoted(v[0]) << ", "
            << std::quoted(v[1]) << " }\n";
  return 0;
}
