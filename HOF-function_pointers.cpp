#include <csignal>
#include <functional>
#include <iostream>
#include <string>
using namespace std;

// overload ostream &operator<< to output address of function ptr
// so (cout << foo) behaves like (cout << &foo)
// without this, (cout << foo) prints true
namespace std {
template <typename P, typename... Args>
std::ostream &operator<<(std::ostream &os, P (*ptr)(Args...)) {
  os << (void *)ptr;
  return os;
}
} // namespace std

// some functions for later use
void foo(int x) { std::cout << "foo: " << x << "\n"; }
string goo(int) { return "yo"; }
int add(int a, double b) { return a + b; }
int add2(int a = 1, double b = 2) { return a + b; }
int divide(int a, int b) { return a / b; }
void say(string s = "hello world") { cout << s << endl; }
void say2things(string s1, string s2) { cout << s1 << " " << s2 << endl; }
void execute(void (*fun)(string), string s) { fun(s); }

void f(int n1, int n2, int n3, const int &n4, int n5) {
  std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}

int main() {
  // Function Pointer syntax:
  // return_type (*identifier)(arguments)
  int (*add_ptr)(int, double) = add;
  int (*const c_add_ptr)(int, double) = add;

  // or put the auto in the bag
  auto add_ptr2 = &add;

  add_ptr(3, 4); // use () to call function - ptr is dereferenced implicitly
  std::invoke(add_ptr, 3, 4); // or call with std::invoke

  (*add_ptr)(3, 4); // explicit dereference works but not needed

  add_ptr = add2; // assign to new function (function signature must match)

  // function pointers do not use default arguments
  // because default arguments are a compile time thing
  // add_ptr();     // error

  // type aliases
  using fun = void (*)(string);
  using saytype = decltype(&say);
  fun say_ptr = say;      //& is implicit
  fun say_ptr2 = &say;    // same as above
  saytype say_ptr3 = say; // using type alias

  // pass a fuction ptr to a function
  execute(say_ptr, "what up");

  // to use a function pointer in lambda, must capture it, unlike functions
  auto say_lambda = [say_ptr](string s) { say_ptr(s); };

  // std::bind arguments to functions - use placeholders for args
  using namespace std::placeholders;
  auto fptr = std::bind(f, 1, _1, 3, _2, std::bind(add, 2, 3));
  fptr(2, 4); // 1 2 3 4 5

  // can bind args to front or back of arg list
  auto prepend_hello = std::bind_front(say2things, "hello");
  auto append_goodbye = std::bind_front(say2things, "goodbye");
  prepend_hello("bob");  // hello bob
  append_goodbye("bob"); // bob goodbye

  // pointers to member functions
  struct S {
    void foo(int x) { cout << "member function S::foo" << endl; }
    static void goo(int x) { cout << "static member function S::goo" << endl; }
  };

  auto member_fun = &S::foo;
  auto static_member_fun = &S::goo;
  S s;
  (s.*member_fun)(2);            // wacky syntax to call member function
  std::invoke(member_fun, s, 2); // nice syntax with std::invoke
  static_member_fun(2);          // simple syntax

  // std::invoke is the universal caller
  std::invoke(add_ptr, 2, 3);    // function
  std::invoke(member_fun, s, 2); // member function (s is interpreted as this)
  std::invoke(say_lambda, "Invoke!"); // lambda

  cout << "printing the address of function say:\n";
  cout << reinterpret_cast<void *>(say) << '\n';
  cout << &say << '\n'; // same as above
  cout << say << '\n';  // also works because of our overload above

  cout << "address of say function: " << say_ptr << endl;
  cout << "address of say pointer:  " << &say_ptr << endl;

  // INFO: std::function provides an interface (type erasure)
  // this allows polymorphism without inheritance (see examples below)
  // BEWARE std::function can be slower (~7x) because they are not inlined
  std::function<int(int, double)> qwer = [](int, double) { return 0; };

  auto lambda = [](int x) { std::cout << "lambda: " << x << "\n"; };
  struct Functor {
    void operator()(int x) { std::cout << "functor: " << x << "\n"; }
  } functor;

  // 1. std::function interface allows different callables in a container:
  std::vector<std::function<void(int)>> vec;
  vec.push_back(foo);
  vec.push_back(lambda);
  vec.push_back(functor);
  for (auto &f : vec)
    f(42);

  // 2. std::function used to store unrelated objects with draw() member:
  struct Circle {
    void draw() { /*...*/ }
  };
  struct Square {
    void draw() { /*...*/ }
  };

  std::vector<std::function<void()>> shapes;
  Circle circle;
  Square square;

  shapes.push_back([&] { circle.draw(); });
  shapes.push_back([&] { square.draw(); });

  for (auto &draw_fn : shapes)
    draw_fn();

  // this achieves something that is natural for dynamic typed languages
  // eg in ruby:
  // shapes = [Circle.new, Square.new]
  // shapes.each { |shape| shape.draw }
  // or in ruby but more explicitely like in c++:
  // circle = Circle.new
  // square = Square.new
  // drawers = [
  //   -> { circle.draw },
  //   -> { square.draw }
  // ]
  //
  // drawers.each(&:call)
}
